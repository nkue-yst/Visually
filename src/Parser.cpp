/**
 * @file    Parser.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Parser.hpp"
#include "Node.hpp"
#include "Token.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>

Parser::Parser() noexcept
{}

Node* Parser::parse(std::vector<Token*>& token_list)
{
    this->parsing_token = token_list.begin();

    return this->parseProgram();
}

Node* Parser::parseProgram()
{
    return this->parseOperator();
}

Node* Parser::parseOperator()
{
    Node* node = this->parseNum();

    while (true)
    {
        if (this->checkNextToken("+"))
        {
            Node* add_node  = new Node();
            add_node->type  = NodeType::ADD;
            add_node->left  = node;
            add_node->right = this->parseNum();
            node = add_node;
        }
        else if (this->checkNextToken("-"))
        {
            Node* sub_node  = new Node();
            sub_node->type  = NodeType::SUB;
            sub_node->left  = node;
            sub_node->right = this->parseNum();
            node = sub_node;
        }
        else
        {
            return node;
        }
    }
}

bool Parser::checkNextToken(std::string str)
{
    Token* token = *this->parsing_token;

    if (token->type == TokenType::TK_EOF)
    {
        return false;
    }

    if (std::strncmp(str.c_str(), token->token_head, token->len) == 0)
    {
        this->parsing_token++;
        return true;
    }

    return false;
}

Node* Parser::parseNum()
{
    Node* node = new Node();
    node->type = NodeType::NUM;
    Token* target_token = *(this->parsing_token);
    node->value = std::atoi(target_token->token_head);

    this->parsing_token++;

    return node;
}
