// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef LEXER_H_
#define LEXER_H_

// C++ libraries.
#include <string>

namespace bc
{
    class Lexer
    {
    public:
        bool LexString(const std::string& source, std::string& err_msg);
        bool LexFile(const std::string& file_path, std::string& err_msg);
        std::string ToString();
        ~Lexer();

    private:
        struct LexerImpl;
        LexerImpl* pimpl_ = nullptr;
    };
}

#endif // LEXER_H_