#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Parser
{
public:
    struct Token
    {
        enum class Type
        {
            Invalid = -1,
            BraceOpen,
            BraceClose,
            Space,
            Content,
        };

        static Type getType(char symbol);

        void clear();

        Type type{Type::Invalid};
        std::string str;
    };

    struct Node
    {
        Token token{}; // for leaves
        std::vector<std::unique_ptr<Node>> children;
    };

public:
    explicit Parser(std::string code);

    [[nodiscard]] bool isValid() const { return is_valid_; }

    // debug
    void printTokens() const;
    void printTree() const;

    Node *getRoot() const { return tree_root_.get(); }

private:
    void extract_tokens();
    void prepare_tokens();
    void build_tree();
    int build_tree_r(Node *parent, int token_pos);

private:
    std::string code_;
    bool is_valid_{true};

    std::vector<Token> tokens_;

    std::unique_ptr<Node> tree_root_;
};
