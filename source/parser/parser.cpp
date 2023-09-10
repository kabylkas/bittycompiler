// Copyright (c) 2023 texer.ai. All rights reserved.
#include "parser.h"

// C++ libraries.
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// Local libraries.
#include "token.h"

namespace bc
{
    // Constant error messages.

    struct Parser::ParserImpl
    {
        std::vector<Token> tokens;
    };

    static void Split(const std::string& str, char delimeter, std::vector<std::string>& str_vec)
    {
        size_t start = 0;
        size_t pos = str.find(delimeter);

        if (pos != std::string::npos)
        {
            std::string substr = str;
            while (pos != std::string::npos)
            {
                str_vec.push_back(substr.substr(0, pos));
                substr = substr.substr(pos + 1);
                pos = substr.find(delimeter);
            }
        }
    }

    static void Strip(std::string& str)
    {
        auto new_end_iter = std::remove_if(str.begin(), str.end(), [&](const char c) {
            return c == '\n';
        });
        str.erase(new_end_iter);
    }

    bool Parser::ParseString(const std::string& tokens, std::string& err_msg)
    {
        bool should_abort = false;
        if (pimpl_ == nullptr)
        {
            pimpl_ = new ParserImpl;
        }

        std::vector<std::string> str_tokens;
        Split(tokens, ';', str_tokens);

        for (std::string& single_str_token : str_tokens)
        {
            Strip(single_str_token);
            pimpl_->tokens.push_back(Token());
            pimpl_->tokens.back().Tokenize(single_str_token);
        }

        return !should_abort;
    }

    Parser::~Parser()
    {
        if (pimpl_ != nullptr)
        {
            delete pimpl_;
            pimpl_ = nullptr;
        }
    }
}
