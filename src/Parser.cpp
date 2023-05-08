#include "Parser.h"

#include <algorithm>

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
    tree_root_ = std::make_unique<TreeNode>();
    build_tree_r(tree_root_.get(), 0);
}

int Parser::build_tree_r(TreeNode *parent, int token_pos)
{
    for (; token_pos < tokens_.size(); ++token_pos)
    {
        const Token &token = tokens_[token_pos];
        if (token.type == Token::Type::Content)
        {
            std::unique_ptr<TreeNode> child = std::make_unique<TreeNode>();
            child->token = token;
            parent->children.push_back(std::move(child));
        }
        else if (token.type == Token::Type::BraceOpen)
        {
            std::unique_ptr<TreeNode> child = std::make_unique<TreeNode>();
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