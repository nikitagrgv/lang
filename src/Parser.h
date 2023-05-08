#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Parser
{
public:
    explicit Parser(std::string code)
        : code_(std::move(code))
    {
        extract_tokens();
        prepare_tokens();

        std::cout << "tokens\n";
        for (const Token &t : tokens_)
        {
            std::cout << (int)t.type << " : " << t.str << std::endl;
        }

        build_tree();


        std::cout << "tree\n";
        std::function<void(TreeNode *, int)> print_tree;
        print_tree = [&print_tree](TreeNode *node, const int depth) {
            for (int i = 0; i < depth; ++i)
            {
                std::cout << "    ";
            }
            const std::string name = node->token.type == Token::Type::Invalid ? std::string(".")
                                                                              : node->token.str;
            std::cout << name << std::endl;

            for (const auto &child : node->children)
            {
                print_tree(child.get(), depth + 1);
            }
        };
        print_tree(tree_root_.get(), 0);
    }

    [[nodiscard]] bool isValid() const { return is_valid_; }

private:
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

        static Type getType(char symbol)
        {
            switch (symbol)
            {
            case '(': return Type::BraceOpen;
            case ')': return Type::BraceClose;
            case ' ':
            case '\n':
            case '\r': return Type::Space;
            default: return Type::Content;
            }
        }

        void clear()
        {
            str.clear();
            type = Type::Invalid;
        }

        Type type{Type::Invalid};
        std::string str;
    };

    struct TreeNode
    {
        Token token{}; // for leaves
        std::vector<std::unique_ptr<TreeNode>> children;
    };


private:
    void extract_tokens();
    void prepare_tokens();
    void build_tree();
    int build_tree_r(TreeNode *parent, int token_pos);

private:
    std::string code_;
    bool is_valid_{true};

    std::vector<Token> tokens_;

    std::unique_ptr<TreeNode> tree_root_;
};
