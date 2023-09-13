// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef AST_H_
#define AST_H_

namespace bc
{
    enum class NodeKind
    {
        kUndefined,
        kProgram,
        kExpression,
        kLabel,
        kStatement
    };

    struct Node
    {
        NodeKind kind = NodeKind::kUndefined;
        std::vector<std::shared_ptr<Node>> subnodes;
    };
}
#endif // AST_H_
