/**
 * @file    Token.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Token.hpp"
#include "Error.hpp"

#include <cctype>
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

    while (*ch_str)
    {
        if (std::isdigit(*ch_str))
        {
            Token* token = new Token(TokenType::NUM, ch_str, 0);

            while (std::isdigit(*ch_str))
            {
                token->len++;
                ch_str++;
            }
            token_list.push_back(token);
        }
        else
        {
            Error::setErrorMsg("invalid char");
            Error::abort();
        }
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

    case TokenType::TK_EOF:
        type = "EOF";
        break;

    case TokenType::UNDEFINED:
        type = "UNDEFINED";
        break;

    default:
        break;
    }

    stream << "[Token]\n" << "type: " << type << "\n" << "len: " << token->len;

    return stream; 
}
