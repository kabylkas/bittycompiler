// Copyright (c) 2023 texer.ai. All rights reserved.
#include "lexer.h"

// C++ libraries.
#include <algorithm>
#include <vector>

// Local libraries.
#include "token.h"

namespace splat
{
    // Constant error messages.
    static const char* kStringErrorUndefinedTokenKind = "Error: Token value is undefined.";

    // Constant string vectors involved in lexing.
    static const std::vector<std::string> kTypeList = {"i32", "u32", "i64", "u64", "bool"};
    static const std::vector<std::string> kStatementTokenList = {"if", "while", "begin", "end", "program", "do", "return"};
    static const std::vector<std::string> kOpTokenList = {"and", "or", "not", ">", "<", "=", "==", ">=", "<=", "+", "-", "*", "/", "%"};

    struct Lexer::LexerImpl
    {
        std::string source;
        std::vector<Token> tokens;
    };

    enum class LexState
    {
        kUndefined,
        kInit,
        kFormValue,
        kFormStringValue,
        kFormTwoCharOperator,
        kFinalizeValue
    };

    static bool IsAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    static bool IsNumber(char c)
    {
        return (c >= '0' && c <= '9');
    }

    static bool CharInString(char c, const std::string& str)
    {
        return str.find(c) != std::string::npos;
    }

    static TokenKind GetTokenKind(const std::string& token_value)
    {
        bool is_statement_token = std::find(kStatementTokenList.begin(), kStatementTokenList.end(), token_value) != std::end(kStatementTokenList);
        bool is_operator_token = std::find(kOpTokenList.begin(), kOpTokenList.end(), token_value) != std::end(kOpTokenList);

        if (is_statement_token)
        {
            return TokenKind::kStatement;
        }
        else if (is_operator_token)
        {
            return TokenKind::kOperator;
        }
        else if (token_value.length() == 1 && CharInString(token_value[0], "()"))
        {
            return TokenKind::kSpecialChar;
        }

        return TokenKind::kUndefined;
    }

    bool Lexer::LexString(const std::string& source, std::string& err_msg)
    {
        if (pimpl_ == nullptr)
        {
            pimpl_ = new LexerImpl;
        }

        bool should_abort = false;
        std::string token_val;
        LexState state = LexState::kInit;
        for (auto c_iter = source.begin(); !should_abort && c_iter != source.end(); c_iter++)
        {
            char c = *c_iter;

            bool should_get_next_c = false;
            while (!should_get_next_c && !should_abort)
            {
                switch (state)
                {
                case LexState::kInit:
                {
                    if (IsAlpha(c) || IsNumber(c))
                    {
                        token_val = c;
                        state = LexState::kFormValue;
                    }
                    else if (c == '"')
                    {
                        state = LexState::kFormStringValue;
                    }
                    else if (c == '=' || c == '>' || c == '<')
                    {
                        state = LexState::kFormTwoCharOperator;
                    }
                    should_get_next_c = true;
                }
                break;

                case LexState::kFormValue:
                {
                    if (IsAlpha(c) || IsNumber(c))
                    {
                        token_val += c;
                        should_get_next_c = true;
                    }
                    else
                    {
                        state = LexState::kFinalizeValue;
                    }
                }
                break;

                case LexState::kFormStringValue:
                {
                    token_val += c;
                    if (c == '"')
                    {
                        state = LexState::kFinalizeValue;
                    }
                }
                break;

                case LexState::kFormTwoCharOperator:
                {
                    if (c == '=')
                    {
                        token_val += c;
                        c = ' ';
                    }
                    state = LexState::kFinalizeValue;
                }
                break;

                case LexState::kFinalizeValue:
                {
                    TokenKind kind = GetTokenKind(token_val);
                    if (kind != TokenKind::kUndefined)
                    {
                        pimpl_->tokens.push_back({token_val, kind});
                        state = LexState::kInit;
                    }
                    else
                    {
                        should_abort = true;
                        err_msg = kStringErrorUndefinedTokenKind;
                    }
                }
                break;

                default:
                    break;
                }
            }
        }

        return !should_abort;
    }

    Lexer::~Lexer()
    {
        if (pimpl_ != nullptr)
        {
            delete pimpl_;
            pimpl_ = nullptr;
        }
    }
}