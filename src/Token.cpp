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

std::vector<Token*> Token::strToToken(const char* str)
{
    std::vector<Token*> token_list;    // 返り値とする解析したトークンリスト

    /* 入力された文字列を1文字ずつ走査 */
    while (*str)
    {
        char ch = Token::nextChar(str);
        Token* new_token = nullptr;

        // 予約語かどうかを検索（何番目の予約後かを記録）
        int32_t reserved_index = searchReservedWord(str);    

        if (reserved_index >= 0)
        {
            new_token = createReservedToken(str, reserved_index);
            str += new_token->len;
        }
        else if (ch == '\n' || ch == ';')    // 改行文字の場合
        {
            new_token = new Token(TokenType::EOL, str, 1);
            str++;
        }
        else if (std::isspace(ch))    // 文字が空白文字の場合、何もせずに次の文字へ
        {
            new_token = new Token(TokenType::SPACE, str, 1);
            str++;
        }
        else if (std::isalpha(ch))    // a~z、A~Zであれば変数とする
        {
            new_token = new Token(TokenType::IDENTIFIER, str, 1);

            while (true)    // 複数文字の場合
            {
                str++;
                ch = Token::nextChar(str);

                if (std::isalpha(ch)) new_token->len++;
                else break;
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')    // 文字が演算子の場合
        {
            new_token = new Token(TokenType::OP, str, 1);
            str++;
        }
        else if (ch == '<' || ch == '>')    // 大小比較演算子
        {
            new_token = new Token(TokenType::OP, str, 1);
            str++;
            ch = Token::nextChar(str);

            if (ch == '=')
            {
                new_token->len++;
                str++;
            }
        }
        else if (ch == '=' || ch == '!')    // 同値比較演算子 or 代入演算子
        {
            new_token = new Token(TokenType::OP, str, 1);
            str++;
            ch = Token::nextChar(str);

            if (ch == '=')
            {
                new_token->len++;
                str++;
            }
        }
        else if (ch == '(')
        {
            new_token = new Token(TokenType::L_BRACE, str, 1);
            str++;
        }
        else if (ch == ')')
        {
            new_token = new Token(TokenType::R_BRACE, str, 1);
            str++;
        }
        else if (std::isdigit(ch))    // 文字が数値の場合
        {
            new_token = new Token(TokenType::NUM, str, 1);

            while (true)    // 複数桁の場合
            {
                str++;
                ch = Token::nextChar(str);

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

    token_list.push_back(new EofToken);

    return token_list;
}

int32_t searchReservedWord(const char* str)
{
    int32_t index = 0;

    for (const char* word : reserved)
    {
        if (std::strncmp(str, word, std::strlen(word)) == 0)
        {
            if (str[std::strlen(word)] == ' ')
                return index;
        }
        index++;
    }
    return -1;
}

Token* createReservedToken(const char* str, int32_t index)
{
    return new Token(TokenType::RESERVED, str, std::strlen(reserved[index]));
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
    case TokenType::RESERVED:
        type = "RESERVED";
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

    char content[512];
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
