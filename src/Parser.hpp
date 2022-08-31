/**
 * @file    Parser.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <vector>

/* 構文解析を行うクラス */
class Parser
{
public:
    Parser() noexcept;

    std::vector<struct Node*> parse(std::vector<struct Token*>& token_list);

private:
    // 入力するプログラム
    std::vector<struct Node*> parseProgram();

    // プログラム本文の解析
    struct Node* expression();

    // 加減算を解析
    struct Node* parseAddSub();

    // 乗除算を解析
    struct Node* parseMulDiv();

    // 単項演算子の解析
    struct Node* parseUnary();

    // 数値または['(' + 式 + ')']を解析
    struct Node* parsePrimary();

    // トークンを数値として解析
    struct Node* parseNum();

    // 次のトークンが引数の文字と等しいかをチェック（等しければ読んでいるトークンは次へ進める）
    bool checkNextToken(std::string ch);

    // 解析中のトークン
    std::vector<struct Token*>::iterator parsing_token;
};

#endif
