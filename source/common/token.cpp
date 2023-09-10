// Copyright (c) 2023 texer.ai. All rights reserved.
#include "token.h"

// C++ libraries.
#include <map>
#include <vector>

namespace bc
{
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
        std::vector<uint32_t> pos;
        for (uint32_t i = 0; i < token.length(); i++)
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
            value = token.substr(pos[0] + 1, pos[1] - pos[0] - 1);
            std::string token_kind_str = token.substr(pos[2] + 1, pos[3] - pos[2] - 1);
            if (kStringToTokenKind.count(token_kind_str) > 0)
            {
                kind = kStringToTokenKind.at(token_kind_str);
            }
        }
    }
}
