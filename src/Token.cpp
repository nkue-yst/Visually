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

Token::Token(TokenType type, char* token_head, int32_t len) noexcept
    : type(type)
    , token_head(token_head)
    , len(len)
{}

std::vector<Token> Token::strToToken(char* str)
{
    std::vector<Token> token_list;    // 返り値とする解析したトークンリスト

    while (*str)
    {
        if (std::isdigit(*str))
        {
            Token token = { TokenType::NUM, str, 0 };

            while (std::isdigit(*str))
            {
                token.len++;
                str++;
            }
            token_list.push_back(token);
        }
        else
        {
            Error::setErrorMsg("invalid char");
            Error::abort();
        }
    }

    Token eof_token = { TokenType::TK_EOF, NULL, 0 };
    token_list.push_back(eof_token);

    return token_list;
}
