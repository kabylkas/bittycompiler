// Copyright (c) 2023 texer.ai. All rights reserved.
#include "parser.h"

// C++ libraries.
#include <algorithm>
#include <memory>
#include <vector>

// Local libraries.
#include "ast.h"
#include "token.h"

namespace bc
{
    enum class StatementType
    {
        kUndefined,
        kLabelEqExpression,
        kSingleExpression
    };
    // Constant error messages.
    static const char* kStringErrorInvalidToken = "Error: Invalid string token provided.";

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

    static StatementType DetermineStatementType(const std::vector<std::string>& tokens)
    {

    }

    static std::shared_ptr<Node> BuildStatement(const std::vector<Token>& tokens, std::string& err_msg)
    {

    }

    static bool BuildTree(const std::vector<Token>& tokens, Node& root_node, std::string& err_msg)
    {
        uint32_t i = 1;

        // Find "program" "begin" tokens.
        bool is_program_begin_found = false;
        while (i < tokens.size() && !is_program_begin_found)
        {
            bool are_both_statements = (tokens[i - 1].kind == TokenKind::kStatement) && (tokens[i].kind == TokenKind::kStatement);
            is_program_begin_found = (tokens[i].value == "program") && (tokens[i].value == "begin");
            is_program_begin_found &= are_both_statements;
            ++i;
        }

        if (is_program_begin_found)
        {
            bool is_end_found = false;
            bool should_abort = false;
            while (i < tokens.size() && !is_end_found && !should_abort)
            {
                // Form statement.
                std::vector<Token> statement_tokens;
                bool is_semicol_found = false;
                while (i < tokens.size() && !is_semicol_found)
                {
                    is_semicol_found = tokens[i].kind == TokenKind::kSpecialChar && tokens[i].value == ";";
                    if (!is_semicol_found)
                    {
                        statement_tokens.push_back(tokens[i]);
                    }
                    ++i;
                }

                // Parse statement.
                if (is_semicol_found)
                {
                    std::shared_ptr<Node> statement_node = std::make_shared<Node>();
                    statement_node->kind = NodeKind::kStatement;
                    root_node.subnodes.push_back(statement_node);
                    statement_node = BuildStatement(statement_tokens, err_msg);
                }
            }
        }
    }

    bool Parser::ParseString(const std::string& tokens, std::string& err_msg)
    {
        // Create implementation.
        bool should_abort = false;
        if (pimpl_ == nullptr)
        {
            pimpl_ = new ParserImpl;
        }

        // Tokenize string tokens to tokens in internal representation.
        std::vector<std::string> str_tokens;
        Split(tokens, '\n', str_tokens);

        for (uint32_t i = 0; !should_abort && i < str_tokens.size(); i++)
        {
            std::string& single_str_token = str_tokens[i];
            pimpl_->tokens.push_back(Token());
            pimpl_->tokens.back().Tokenize(single_str_token);
            if (pimpl_->tokens.back().kind == TokenKind::kUndefined)
            {
                should_abort = true;
                err_msg = kStringErrorInvalidToken;
            }
        }

        // Parse tokens into AST.
        if (!should_abort)
        {
            Node root_node;
            bool is_built = BuildTree(pimpl_->tokens, root_node, err_msg);
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
