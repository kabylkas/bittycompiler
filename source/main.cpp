// Copyright (c) 2023 texer.ai. All rights reserved.

// C++ libraries.
#include <sstream>

// Local libraries.
#include "lexer.h"

int main()
{
    std::stringstream source_stream;
    source_stream << "program\n";
    source_stream << "begin\n";
    source_stream << "4+2/2*2;\n";
    source_stream << "end\n";

    std::string err_msg;
    splat::Lexer lexer;
    bool is_lexed = lexer.Lex(source_stream.str(), err_msg);

    return 0;
}