/**
 * @file    Parser.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Parser.hpp"
#include "Node.hpp"
#include "Token.hpp"

#include <cstdlib>
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
    return this->parseNum();
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
