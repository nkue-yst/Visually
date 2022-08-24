/**
 * @file    Parser.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <vector>

/* 構文解析を行うクラス */
class Parser
{
public:
    Parser() noexcept;

    struct Node* parse(std::vector<struct Token>& token_list);

private:
    // 入力するプログラム
    struct Node* parseProgram();

    // トークンを数値として解析
    struct Node* parseNum();

    // 解析中のトークン
    std::vector<struct Token>::iterator parsing_token;
};

#endif
