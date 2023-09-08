// Copyright (c) 2023 texer.ai. All rights reserved.

// C++ libraries.
#include <iostream>
#include <sstream>

// Local libraries.
#include "lexer.h"

int main()
{
    // Test 1.
    {
        std::stringstream source_stream;
        source_stream << "program\n";
        source_stream << "begin\n";
        source_stream << "4+2/2*2;\n";
        source_stream << "40+221/(2*221);\n";
        source_stream << "end\n";

        std::string err_msg;
        bc::Lexer lexer;
        bool is_lexed = lexer.LexString(source_stream.str(), err_msg);

        if (is_lexed)
        {
            std::cout << lexer.ToString() << std::endl;
        }
    }
    return 0;
}