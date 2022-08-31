/**
 * @file    Token.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Token.hpp"
#include "Error.hpp"

#include <cctype>
#include <cstring>
#include <iostream>

Token::Token() noexcept
    : type(TokenType::UNDEFINED)
    , token_head(nullptr)
    , len(0)
{}

Token::Token(TokenType type, const char* token_head, int32_t len) noexcept
    : type(type)
    , token_head(token_head)
    , len(len)
{}

std::vector<Token*> Token::strToToken(std::string str)
{
    std::vector<Token*> token_list;    // 返り値とする解析したトークンリスト

    const char* ch_str = str.c_str();

    /* 入力された文字列を1文字ずつ走査 */
    while (*ch_str)
    {
        char ch = ch_str[0];
        Token* new_token = nullptr;

        if (ch =='\n' || ch == ';')    // 改行文字の場合
        {
            new_token = new Token(TokenType::EOL, ch_str, 1);
            ch_str++;
        }
        else if (std::isspace(ch))    // 文字が空白文字の場合、何もせずに次の文字へ
        {
            new_token = new Token(TokenType::SPACE, ch_str, 1);
            ch_str++;
        }
        else if (std::isalpha(ch))    // a~z、A~Zであれば変数とする
        {
            new_token = new Token(TokenType::IDENTIFIER, ch_str, 1);
            ch_str++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')    // 文字が演算子の場合
        {
            new_token = new Token(TokenType::OP, ch_str, 1);
            ch_str++;
        }
        else if (ch == '(')
        {
            new_token = new Token(TokenType::L_BRACE, ch_str, 1);
            ch_str++;
        }
        else if (ch == ')')
        {
            new_token = new Token(TokenType::R_BRACE, ch_str, 1);
            ch_str++;
        }
        else if (std::isdigit(ch))    // 文字が数値の場合
        {
            new_token = new Token(TokenType::NUM, ch_str, 1);

            while (true)    // 複数桁の場合
            {
                ch_str++;
                ch = ch_str[0];

                if (std::isdigit(ch))
                {
                    new_token->len++;
                }
                else
                {
                    break;
                }
            }
        }
        else    // 未定義文字の場合エラー
        {
            Error::setErrorMsg("invalid char");
            Error::abort();
        }

        token_list.push_back(new_token);
    }

    Token* eof_token = new Token(TokenType::TK_EOF, NULL, 0);
    token_list.push_back(eof_token);

    return token_list;
}

std::ostream& operator<<(std::ostream& stream, const Token* token)
{
    std::string type;

    switch (token->type)
    {
    case TokenType::NUM:
        type = "NUM";
        break;
    case TokenType::OP:
        type = "OP";
        break;
    case TokenType::IDENTIFIER:
        type = "IDENTIFIER";
        break;
    case TokenType::L_BRACE:
    case TokenType::R_BRACE:
        type = "BRACE";
        break;
    case TokenType::SPACE:
        type = "SPACE";
        break;
    case TokenType::EOL:
        type = "EOL";
        break;
    case TokenType::TK_EOF:
        type = "EOF";
        break;
    case TokenType::UNDEFINED:
        type = "UNDEFINED";
        break;
    default:
        break;
    }

    static char content[64];
    std::memset(content, 0, sizeof(content));
    if (token->type == TokenType::EOL)         std::strcpy(content, "EOL");
    else if (token->type == TokenType::TK_EOF) std::strcpy(content, "EOF");
    else                                       std::strncpy(content, token->token_head, token->len);

    stream << "[Token]"   << std::endl
           << "type:    " << type        << std::endl
           << "content: " << content     << std::endl
           << "len:     " << token->len;

    return stream; 
}
