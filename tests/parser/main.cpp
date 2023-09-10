// Copyright (c) 2023 texer.ai. All rights reserved.

// C++ libraries.
#include <iostream>
#include <sstream>

// Local libraries.
#include "parser.h"

int main()
{
    // Test 1.
    {
        std::stringstream tokens_ss;
        tokens_ss << "{val: \"program\", kind : \"statement\"};\n";
        tokens_ss << "{val: \"begin\", kind : \"statement\"};\n";
        tokens_ss << "{val: \"4\", kind : \"num_lit\"};\n";
        tokens_ss << "{val: \"+\", kind : \"op\"};\n";
        tokens_ss << "{val: \"2\", kind : \"num_lit\"};\n";
        tokens_ss << "{val: \"/\", kind : \"op\"};\n";
        tokens_ss << "{val: \"2\", kind : \"num_lit\"};\n";
        tokens_ss << "{val: \"*\", kind : \"op\"};\n";
        tokens_ss << "{val: \"2\", kind : \"num_lit\"};\n";
        tokens_ss << "{val: \";\", kind : \"spec_char\"};\n";
        tokens_ss << "{val: \"end\", kind : \"statement\"};\n";

        bc::Parser parser;
        std::string err_msg;
        bool is_parsed = parser.ParseString(tokens_ss.str(), err_msg);
    }
    return 0;
}
