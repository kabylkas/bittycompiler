// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef TOKEN_H_
#define TOKEN_H_

// C++ libraries.
#include <string>

namespace splat
{
    enum class TokenKind
    {
        kUndefined,
        kLiteral,
        kSpecialChar,
        kOperator,
        kStatement,
        kType,
        kLabel
    };

    struct Token
    {
        std::string value;
        TokenKind kind = TokenKind::kUndefined;
    };
}

#endif // TOKEN_H_