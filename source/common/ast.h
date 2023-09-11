// Copyright (c) 2023 texer.ai. All rights reserved.
#ifndef AST_H_
#define AST_H_

namespace bc
{
    enum class NodeKind
    {
        kUndefined,
        kStatement,
        kExpression,
        kLabel,
        kStatement
    };

    struct Node
    {
        NodeKind kind = NodeKind::kUndefined;
        std::shared_ptr<Node> subnodes;
    };
}
#endif // AST_H_
