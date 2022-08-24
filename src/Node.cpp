/**
 * @file    Node.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/24
 */

#include "Node.hpp"

Node::Node() noexcept
    : type(NodeType::UNDIFINED)
    , left(nullptr)
    , right(nullptr)
    , value(0)
{}
