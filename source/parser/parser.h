// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef PARSER_H_
#define PARSER_H_

// C++ libraries.
#include <string>

namespace bc
{
    class Parser
    {
    public:
        bool ParseString(const std::string& tokens, std::string& err_msg);
        ~Parser();

    private:
        struct ParserImpl;
        ParserImpl* pimpl_ = nullptr;
    };
}
#endif // PARSER_H_
