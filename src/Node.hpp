/**
 * @file    Node.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <cstdint>

/* ノードの種類 */
enum class NodeType
{
    NUM,          // 数値
    ADD,          // 加算演算子
    SUB,          // 減算演算子
    MUL,          // 乗算
    DIV,          // 除算
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
    {}

    // ノードの種類
    NodeType type;

    // 左の子ノード
    Node* left;

    // 右の子ノード
    Node* right;

    // 数値を格納
    int32_t value;
};

#endif
