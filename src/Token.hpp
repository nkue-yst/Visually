/**
 * @file    Token.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <cstdint>
#include <vector>

/* 入力文字列を分解したトークンの種類 */
enum class TokenType
{
    NUM,          // 数値
    TK_EOF,       // 終端文字
    UNDEFINED,    // 未定義
};

/* 入力文字列を分解したトークンの定義 */
struct Token
{
public:
    Token() noexcept;
    Token(TokenType type, char* token_head, int32_t len) noexcept;

    // 入力文字列をトークンに変換する
    static std::vector<Token> strToToken(char* str);

    // トークンの種類
    TokenType type;

    // トークン開始地点
    char* token_head;

    // トークンの長さ
    int32_t len;
};

#endif
