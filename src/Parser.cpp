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

std::vector<Node*> Parser::parse(std::vector<Token*>& token_list)
{
    this->parsing_token = token_list.begin();

    return this->parseProgram();
}

std::vector<Node*> Parser::parseProgram()
{
    std::vector<Node*> node_list;
    node_list.push_back(this->statement());

    while (this->checkNextToken(";") || this->checkNextToken("\n"))
    {
        node_list.push_back(this->statement());
    }

    return node_list;
}

Node* Parser::statement()
{
    Node* stmt_node = nullptr;
    
    if (this->checkNextToken("return"))
    {
        stmt_node = new Node();
        stmt_node->type = NodeType::RETURN;
        stmt_node->left = this->expression();
    }
    else
    {
        stmt_node = this->expression();
    }

    return stmt_node;
}

Node* Parser::expression()
{
    // 次のトークンが空白文字の場合、次の文字まで飛ばす
    while (this->checkNextToken(" "))
    {}

    Token* token = *(this->parsing_token);

    /* 識別子（変数名）の場合 */
    if (token->type == TokenType::IDENTIFIER)
    {
        this->parsing_token++;

        Node* identifier_node = new Node();
        identifier_node->type = NodeType::IDENTIFIER;
        char var_name[64];
        memset(var_name, 0, sizeof(var_name));
        std::strncpy(var_name, token->token_head, token->len);
        identifier_node->var_name = var_name;

        // 次のトークンが空白文字の場合、次の文字まで飛ばす
        while (this->checkNextToken(" "))
        {}

        if (this->checkNextToken("="))    // 変数代入文
        {
            Node* assign_node = new Node();
            assign_node->type = NodeType::ASSIGN;
            assign_node->left = identifier_node;
            assign_node->right = this->parseCompare();

            return assign_node;
        }
        else
        {
            this->parsing_token--;
        }
    }

    return this->parseCompare();
}

Node* Parser::parseCompare()
{
    // 次のトークンが空白文字の場合、次の文字まで飛ばす
    while (this->checkNextToken(" "))
    {}

    Node* root_node = this->parseAddSub();
    Node* cmp_node = nullptr;

    if (this->checkNextToken("=="))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::EQUAL;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else if (this->checkNextToken("!="))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::NEQUAL;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else if (this->checkNextToken("<"))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::LESS;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else if (this->checkNextToken(">"))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::GREATER;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else if (this->checkNextToken("<="))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::LESSEQ;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else if (this->checkNextToken(">="))
    {
        cmp_node = new Node();
        cmp_node->type = NodeType::GREATEREQ;
        cmp_node->left = root_node;
        cmp_node->right = this->parseAddSub();
    }
    else
    {
        return root_node;
    }

    return cmp_node;
}

Node* Parser::parseAddSub()
{
    Node* root_node = this->parseMulDiv();     // まずは乗算・除算を解析

    while (true)
    {
        if (this->checkNextToken(" "))         // 空白文字は読み飛ばす
        {}
        else if (this->checkNextToken("+"))    // 加算演算子の場合
        {
            Node* add_node  = new Node();
            add_node->type  = NodeType::ADD;
            add_node->left  = root_node;
            add_node->right = this->parseMulDiv();
            root_node = add_node;
        }
        else if (this->checkNextToken("-"))    // 減算演算子の場合
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
    Node* root_node = this->parseUnary();

    while (true)
    {
        if (this->checkNextToken(" "))         // 空白文字は読み飛ばす
        {}
        else if (this->checkNextToken("*"))
        {
            Node* mul_node  = new Node();
            mul_node->type  = NodeType::MUL;
            mul_node->left  = root_node;
            mul_node->right = this->parseUnary();
            root_node = mul_node;
        }
        else if (this->checkNextToken("/"))
        {
            Node* div_node  = new Node();
            div_node->type  = NodeType::DIV;
            div_node->left  = root_node;
            div_node->right = this->parseUnary();
            root_node = div_node;
        }
        else
        {
            return root_node;
        }
    }
}

Node* Parser::parseUnary()
{
    // 次のトークンが空白文字の場合、次の文字まで飛ばす
    while (this->checkNextToken(" "))
    {}

    if (checkNextToken("+"))    // 前置演算子'+'の場合はそのまま次の式を解析
    {
        return this->parsePrimary();
    }
    else if (checkNextToken("-"))    // 前置演算子'-'の場合
    {
        /* 0の数値ノードを生成 */
        Node* zero_node = new Node();
        zero_node->type = NodeType::NUM;
        zero_node->value = 0;

        /* 0-(num)の形でノード生成 */
        Node* node = new Node();
        node->type = NodeType::SUB;
        node->left = zero_node;
        node->right = this->parsePrimary();

        return node;
    }
    else    // 前置演算子無しの式を解析
    {
        return this->parsePrimary();
    }
}

Node* Parser::parsePrimary()
{
    // 次のトークンが空白文字の場合、次の文字まで飛ばす
    while (this->checkNextToken(" "))
    {}

    // 次のトークンが'('であれば式が来る
    if (this->checkNextToken("("))
    {
        Node* node = this->expression();    // 次のトークンから式ノード作成
        if (!this->checkNextToken(")"))     // 次のトークンが')'であれば
        {
            Error::setErrorMsg("invalid expression");
            Error::abort();
        }

        return node;    // 括弧内の式のルートノードを返す
    }

    return this->parseNum();    // 次のトークンが'('でなければ整数値を返す
}

Node* Parser::parseNum()
{
    Token* target_token = *(this->parsing_token);

    Node* node = new Node();

    if (target_token->type == TokenType::IDENTIFIER)    // 変数の場合
    {
        node->type = NodeType::ID_VAR;
        char var_name[512];
        memset(var_name, 0, sizeof(var_name));
        std::strncpy(var_name, target_token->token_head, target_token->len);
        node->var_name = var_name;
    }
    else if (target_token->type == TokenType::NUM)    // 整数定数の場合
    {
        node->type = NodeType::NUM;
        node->value = std::atoi(target_token->token_head);
    }

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
