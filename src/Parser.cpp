/**
 * @file    Parser.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Parser.hpp"
#include "Error.hpp"
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
    return this->expression();
}

Node* Parser::expression()
{
    Node* root_node = this->parseMulDiv();    // まずは乗算・除算を解析

    while (true)
    {
        if (this->checkNextToken("+"))
        {
            Node* add_node  = new Node();
            add_node->type  = NodeType::ADD;
            add_node->left  = root_node;
            add_node->right = this->parseMulDiv();
            root_node = add_node;
        }
        else if (this->checkNextToken("-"))
        {
            Node* sub_node  = new Node();
            sub_node->type  = NodeType::SUB;
            sub_node->left  = root_node;
            sub_node->right = this->parseMulDiv();
            root_node = sub_node;
        }
        else
        {
            return root_node;
        }
    }
}

Node* Parser::parseMulDiv()
{
    Node* root_node = this->parsePrimary();

    while (true)
    {
        if (this->checkNextToken("*"))
        {
            Node* mul_node  = new Node();
            mul_node->type  = NodeType::MUL;
            mul_node->left  = root_node;
            mul_node->right = this->parsePrimary();
            root_node = mul_node;
        }
        else if (this->checkNextToken("/"))
        {
            Node* div_node  = new Node();
            div_node->type  = NodeType::DIV;
            div_node->left  = root_node;
            div_node->right = this->parsePrimary();
            root_node = div_node;
        }
        else
        {
            return root_node;
        }
    }
}

Node* Parser::parsePrimary()
{
    // 次のトークンが'('であれば式が来る
    if (this->checkNextToken("("))
    {
        Node* node = this->expression();    // 次のトークンから式ノード作成
        if (!this->checkNextToken(")"))     // 次のトークンが')'であれば
        {
            Error::setErrorMsg("invalid expression");
            Error::abort();
        }
    }

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
