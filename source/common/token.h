// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef TOKEN_H_
#define TOKEN_H_

// C++ libraries.
#include <string>

namespace bc
{
    enum class TokenKind
    {
        kUndefined,
        kStringLiteral,
        kNumberLiteral,
        kSpecialChar,
        kOperator,
        kStatement,
        kType,
        kLabel
    };

    struct Token
    {
        void Tokenize(const std::string& token);
        std::string ToString();
        std::string value;
        TokenKind kind = TokenKind::kUndefined;
    };
}

#endif // TOKEN_H_
