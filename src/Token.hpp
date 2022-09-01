/**
 * @file    Token.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

static const char* reserved[] =
{
    "return",
};

/* 入力文字列を分解したトークンの種類 */
enum class TokenType
{
    NUM,          // 数値
    OP,           // 演算子
    IDENTIFIER,   // 識別子（変数）

    L_BRACE,      // '('
    R_BRACE,      // ')'
    SPACE,        // 空白文字

    RESERVED,     // 予約語

    EOL,          // 改行文字
    TK_EOF,       // 終端文字
    UNDEFINED,    // 未定義
};

/* 入力文字列を分解したトークンの定義 */
struct Token
{
public:
    Token() noexcept;
    Token(TokenType type, const char* token_head, int32_t len) noexcept;

    // 入力文字列をトークンに変換する
    static std::vector<Token*> strToToken(const char* str);

    // トークンの種類
    TokenType type;

    // トークン開始地点
    const char* token_head;

    // トークンの長さ
    int32_t len;

private:
    // 文字列の次の文字を返す
    static char nextChar(const char*& str) noexcept { return str[0]; }
};

/* EOFトークン */
struct EofToken : public Token
{
    EofToken() noexcept
        : Token(TokenType::TK_EOF, nullptr, 0)
    {}
};

int32_t searchReservedWord(const char* str);
Token* createReservedToken(const char* str, int32_t index);

// トークン情報出力処理
std::ostream& operator<<(std::ostream& stream, const Token* token);

#endif
