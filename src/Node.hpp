/**
 * @file    Node.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <cstdint>
#include <iostream>

static std::ostream& operator<<(std::ostream& stream, const Node* node);    // ノード情報出力処理（前方宣言）

/* ノードの種類 */
enum class NodeType
{
    NUM,          // 数値
    ADD,          // 加算演算子
    SUB,          // 減算演算子
    MUL,          // 乗算
    DIV,          // 除算
    ASSIGN,       // 代入演算子

    EQUAL,        // ==
    NEQUAL,       // !=
    LESS,         // <
    GREATER,      // >
    LESSEQ,       // <=
    GREATEREQ,    // >=

    IDENTIFIER,   // 識別子

    RETURN,       // return文

    ID_VAR,       // 変数
    UNDIFINED,    // 未定義
};

/* 構文解析結果を表現するためのノード */
struct Node
{
public:
    Node() noexcept
        : type(NodeType::UNDIFINED)
        , left(nullptr)
        , right(nullptr)
        , value(0)
        , var_name("")
    {}

    ~Node() noexcept
    {
        delete this->left;
        delete this->right;
    }

    // ルートノードから再帰的に全ノード情報を出力
    void printChildren(uint32_t start_depth)
    {
        // 左の子ノード情報を出力
        if (this->left)
        {
            std::cout << this->left << std::endl;
            std::cout << "depth: " << start_depth << std::endl << std::endl;
            this->left->printChildren(start_depth + 1);
        }

        // 右の子ノード情報を出力
        if (this->right)
        {
            std::cout << this->right << std::endl;
            std::cout << "depth: " << start_depth << std::endl << std::endl;
            this->right->printChildren(start_depth + 1);
        }
    }

    // ノードの種類
    NodeType type;

    // 左の子ノード
    Node* left;

    // 右の子ノード
    Node* right;

    // 数値を格納
    int32_t value;

    // 変数の場合の変数名
    std::string var_name;
};

// ノード情報出力処理
static std::ostream& operator<<(std::ostream& stream, const Node* node)
{
    std::string type;

    switch (node->type)
    {
    case NodeType::NUM:
        type = "NUM";
        break;
    case NodeType::ADD:
        type = "ADD";
        break;
    case NodeType::SUB:
        type = "SUB";
        break;
    case NodeType::MUL:
        type = "MUL";
        break;
    case NodeType::DIV:
        type = "DIV";
        break;
    case NodeType::ASSIGN:
        type = "ASSIGN";
        break;
    case NodeType::EQUAL:
        type = "EQUAL";
        break;
    case NodeType::NEQUAL:
        type = "NEQUAL";
        break;
    case NodeType::LESS:
        type = "LESS";
        break;
    case NodeType::GREATER:
        type = "GREATER";
        break;
    case NodeType::LESSEQ:
        type = "LESSEQ";
        break;
    case NodeType::GREATEREQ:
        type = "GREATEREQ";
        break;
    case NodeType::IDENTIFIER:
        type = "IDENTIFIER";
        break;
    case NodeType::RETURN:
        type = "RETURN";
        break;
    case NodeType::ID_VAR:
        type = "ID_VAR";
        break;
    default:
        break;
    }

    stream << "[Node]" << std::endl
           << "type: " << type;

    if (node->type == NodeType::NUM)
        stream << std::endl << "value: " << node->value;
    else if (node->type == NodeType::IDENTIFIER || node->type == NodeType::ID_VAR)
        stream << std::endl << "name: " << node->var_name;

    return stream;
}

#endif
