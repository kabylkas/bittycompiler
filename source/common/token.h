// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef TOKEN_H_
#define TOKEN_H_

// C++ libraries.
#include <string>
#include <vector>

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
        Token(TokenKind kind, const std::string& value) : kind_(kind), value_(value) {};

        void Tokenize(const std::string& token);
        bool IsValid() const;
        std::string GetValue() const;
        TokenKind GetKind() const;

    private:
        std::string value_;
        TokenKind kind_ = TokenKind::kUndefined;
        uint32_t line_ = 0;
        uint32_t column_ = 0;
    };

    class TokenStream
    {
    public:
        TokenStream(const std::vector<Token>& tokens) : tokens_(tokens) {};
        const Token& Peek() const;
        const Token& PeekNext() const;
        const Token& PeekCurrentPlus(size_t offset) const;
        bool IsStreamEnd() const;

        // Operator overloads.
        void operator++();

    private:
        const std::vector<Token> tokens_;
        size_t current_idx_ = 0;
    };
}

#endif // TOKEN_H_
