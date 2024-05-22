// Copyright (c) 2023 texer.ai. All rights reserved.
#include "token.h"

// C++ libraries.
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

namespace bc
{
    // Messages.
    static const char* kStringWarningOutOfRange = "Warning: Trying to peek out of range token.";

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

    // Constant map for token enum to string conversion.
    static const std::map<std::string, TokenKind> kStringToTokenKind = {
        {"label", TokenKind::kLabel},
        {"num_lit", TokenKind::kNumberLiteral},
        {"op", TokenKind::kOperator},
        {"spec_char", TokenKind::kSpecialChar},
        {"statement", TokenKind::kStatement},
        {"str_lit", TokenKind::kStringLiteral},
        {"type", TokenKind::kType}
    };

    void Token::Tokenize(const std::string& token)
    {
        // Example of a string token: {val: "+", kind: "op"};
        // Valid token should contain four quotes.
        std::vector<int32_t> pos;
        for (int32_t i = 0; i < token.length(); i++)
        {
            if (token[i] == '\"')
            {
                pos.push_back(i);
            }
        }
        bool is_valid = (pos.size() == 4) && (pos[0] != std::string::npos) && (pos[1] != std::string::npos)
            && (pos[2] != std::string::npos) && (pos[3] != std::string::npos);

        if (is_valid)
        {
            assert(pos[1] - pos[0] > 0);
            value_ = token.substr(pos[0] + 1, pos[1] - pos[0] - 1);
            std::string token_kind_str = token.substr(pos[2] + 1, pos[3] - pos[2] - 1);
            if (kStringToTokenKind.count(token_kind_str) > 0)
            {
                kind_ = kStringToTokenKind.at(token_kind_str);
            }
        }
    }

    Token::Token(const std::string& token)
    {
        Tokenize(token);
    }

    bool Token::IsValid() const
    {
        return kind_ != TokenKind::kUndefined;
    }

    std::string Token::GetValue() const
    {
        return value_;
    }

    TokenKind Token::GetKind() const
    {
        return kind_;
    }

    const Token& TokenStream::PeekCurrentPlus(size_t offset) const
    {
        if (current_idx_ + offset < tokens_.size())
        {
            return tokens_[current_idx_];
        }
        else
        {
            std::cerr << kStringWarningOutOfRange << std::endl;
        }
        return tokens_[0];
    }

    const Token& TokenStream::Peek() const
    {
        return PeekCurrentPlus(0);
    }

    const Token& TokenStream::PeekNext() const
    {
        return PeekCurrentPlus(1);
    }

    bool TokenStream::IsStreamEnd() const
    {
        return current_idx_ >= tokens_.size();
    }
}
