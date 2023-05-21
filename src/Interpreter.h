#pragma once

#include <memory>
#include <variant>
#include <vector>

class ExprNode
{
public:



private:
    std::vector<std::unique_ptr<ExprNode>> children_;
};


class Interpreter
{
public:
    Interpreter();

    enum class Operator
    {
        None = -1,
        Plus,
        Minus,
        Mul,
        Divide,
    };

    using Value = std::variant<float>;


public:



private:
    struct Node
    {
        // for leaves
        Value value{};

        Operator op{Operator::None};
        std::vector<std::unique_ptr<Node>> children;
    };

private:
    std::unique_ptr<Node> root_;
};
