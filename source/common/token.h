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

    class Token
    {
    public:
        Token(const std::string& token);
        void Tokenize(const std::string& token);
        std::string ToString();
        bool IsValid() const;

    private:
        std::string value_;
        TokenKind kind_ = TokenKind::kUndefined;
    };
}

#endif // TOKEN_H_
