#include "Parser.h"

#include <algorithm>

Parser::Parser(std::string code)
    : code_(std::move(code))
{
    extract_tokens();
    prepare_tokens();

    // debug
    printTokens();

    build_tree();

    // debug
    printTree();
}

void Parser::extract_tokens()
{
    Token cur_token;
    cur_token.type = Token::Type::Content;
    for (const char &sym : code_)
    {
        Token::Type type = Token::getType(sym);
        if (cur_token.type != type && cur_token.type != Token::Type::Invalid)
        {
            tokens_.push_back(cur_token);
            cur_token.clear();
        }

        cur_token.type = type;
        cur_token.str.push_back(sym);

        if (cur_token.type == Token::Type::BraceClose || cur_token.type == Token::Type::BraceOpen)
        {
            tokens_.push_back(cur_token);
            cur_token.clear();
        }
    }
    if (cur_token.type != Token::Type::Invalid)
    {
        tokens_.push_back(cur_token);
    }
}

void Parser::prepare_tokens()
{
    tokens_.erase(std::remove_if(tokens_.begin(), tokens_.end(),
                      [](const Token &token) { return token.type == Token::Type::Space; }),
        tokens_.end());
}

void Parser::build_tree()
{
    tree_root_ = std::make_unique<Node>();
    build_tree_r(tree_root_.get(), 0);
}

int Parser::build_tree_r(Node *parent, int token_pos)
{
    for (; token_pos < tokens_.size(); ++token_pos)
    {
        const Token &token = tokens_[token_pos];
        if (token.type == Token::Type::Content)
        {
            std::unique_ptr<Node> child = std::make_unique<Node>();
            child->token = token;
            parent->children.push_back(std::move(child));
        }
        else if (token.type == Token::Type::BraceOpen)
        {
            std::unique_ptr<Node> child = std::make_unique<Node>();
            parent->children.push_back(std::move(child));
            token_pos = build_tree_r(parent->children.back().get(), token_pos + 1); // -1?
        }
        else if (token.type == Token::Type::BraceClose)
        {
            return token_pos;
        }
    }

    return token_pos;
}

void Parser::printTokens() const
{
    std::cout << "tokens\n";
    for (const Token &t : tokens_)
    {
        std::cout << (int)t.type << " : " << t.str << std::endl;
    }
}

void Parser::printTree() const
{
    std::cout << "tree:\n";
    std::function<void(Node *, int)> print_tree;
    print_tree = [&print_tree](Node *node, const int depth) {
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

Parser::Token::Type Parser::Token::getType(char symbol)
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

void Parser::Token::clear()
{
    str.clear();
    type = Type::Invalid;
}
