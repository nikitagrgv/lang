#pragma once

#include <memory>
#include <variant>
#include <vector>

class Interpreter
{
public:
    Interpreter();

    using Value = std::variant<float>;

    enum class Operator
    {
        None = -1,
        Plus,
        Minus,
        Mul,
        Divide,
    };



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
