/**
 * @file    Parser.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Parser.hpp"
#include "Node.hpp"
#include "Token.hpp"

#include <cstdlib>

Parser::Parser() noexcept
{}

Node* Parser::parseProgram()
{
    return this->parseNum();
}

Node* Parser::parseNum()
{
    Node* node = new Node();
    node->type = NodeType::NUM;
    node->value = std::atoi(this->parsing_token->token_head);

    this->parsing_token++;

    return node;
}

Node* Parser::parse(std::vector<Token>& token_list)
{
    this->parsing_token = token_list.begin();

    return this->parseProgram();
}
