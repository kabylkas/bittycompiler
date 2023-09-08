// Copyright (c) 2023 texer.ai. All rights reserved.
#include "lexer.h"

// C++ libraries.
#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include <vector>

// Local libraries.
#include "token.h"

namespace bc
{
    // Constant error messages.
    static const char* kStringErrorUndefinedTokenKind = "Error: Token value is undefined.";
    static const char* kStringErrorFailedFormingString = "Error: Could not form string, quotes were not closed.";

    // Constant string vectors involved in lexing.
    static const std::vector<std::string> kTypeList = {"i32", "u32", "i64", "u64", "bool"};
    static const std::vector<std::string> kStatementTokenList = {"if", "while", "begin", "end", "program", "do", "return"};
    static const std::vector<std::string> kOpTokenList = {"and", "or", "not", ">", "<", "=", "==", ">=", "<=", "+", "-", "*", "/", "%"};
    static const std::vector<std::string> kSpecialCharTokenList = {"(", ")", ";"};

    // Constant map for token enum to string conversion.
    static const std::map<TokenKind, const char*> kTokenKindToString = {
        {TokenKind::kLabel, "label"},
        {TokenKind::kNumberLiteral, "num_lit"},
        {TokenKind::kOperator, "op"},
        {TokenKind::kSpecialChar, "spec_char"},
        {TokenKind::kStatement, "statement"},
        {TokenKind::kStringLiteral, "str_lit"},
        {TokenKind::kType, "type"}
    };

    struct Lexer::LexerImpl
    {
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

    static bool IsOperator(char c)
    {
        for (const auto& op : kOpTokenList)
        {
            if (op.length() == 1 && op[0] == c)
            {
                return true;
            }
        }
        return false;
    }

    static bool IsSpecialChar(char c)
    {
        for (const auto& special_char : kSpecialCharTokenList)
        {
            if (special_char[0] == c)
            {
                return true;
            }
        }
        return false;
    }

    static TokenKind GetTokenKind(const std::string& token_value)
    {
        bool is_statement_token = std::find(kStatementTokenList.begin(), kStatementTokenList.end(), token_value) != std::end(kStatementTokenList);
        bool is_operator_token = std::find(kOpTokenList.begin(), kOpTokenList.end(), token_value) != std::end(kOpTokenList);

        if (token_value.length() > 0)
        {
            if (is_statement_token)
            {
                return TokenKind::kStatement;
            }
            else if (is_operator_token)
            {
                return TokenKind::kOperator;
            }
            else if (token_value.length() == 1 && CharInString(token_value[0], "();"))
            {
                return TokenKind::kSpecialChar;
            }
            else if (token_value.length() > 1 && token_value[0] == '"' && token_value[token_value.length() - 1] == '"')
            {
                return TokenKind::kStringLiteral;
            }
            else if (IsNumber(token_value[0]))
            {
                auto alpha_iter = std::find_if(token_value.begin(), token_value.end(), [&](const char& c) {
                    return IsAlpha(c);
                });
                if (alpha_iter == token_value.end())
                {
                    return TokenKind::kNumberLiteral;
                }
            }
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
                    // Reset token value.
                    token_val = "";

                    // Determine how the value should be formed based on the first char.
                    if (IsAlpha(c) || IsNumber(c))
                    {
                        state = LexState::kFormValue;
                    }
                    else if (c == '"')
                    {
                        state = LexState::kFormStringValue;
                    }
                    else if (c == '=' || c == '>' || c == '<')
                    {
                        token_val = c;
                        state = LexState::kFormTwoCharOperator;
                        should_get_next_c = true;
                    }
                    else if (IsOperator(c) || IsSpecialChar(c))
                    {
                        token_val = c;
                        state = LexState::kFinalizeValue;
                        should_get_next_c = true;
                    }
                    else if (c == ' ' || c == '\n')
                    {
                        should_get_next_c = true;
                    }
                    else
                    {
                        should_abort = true;
                        err_msg = kStringErrorUndefinedTokenKind;
                    }
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
                    else if (c == '\n')
                    {
                        should_abort = true;
                        err_msg = kStringErrorFailedFormingString;
                    }
                }
                break;

                case LexState::kFormTwoCharOperator:
                {
                    if (c == '=')
                    {
                        token_val += c;
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

    std::string Lexer::ToString()
    {
        std::stringstream result_ss;
        for (Token& token : pimpl_->tokens)
        {
            assert(kTokenKindToString.count(token.kind) > 0);
            result_ss << "{val: \"" << token.value << "\", kind: \"" << kTokenKindToString.at(token.kind) << "\"};\n";
        }
        return result_ss.str();
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