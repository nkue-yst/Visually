/**
 * @file    CodeGenerator.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"
#include "Node.hpp"

std::vector<Operation> CodeGenerator::generateCode(Node* node) noexcept
{
    switch (node->type)
    {
    case NodeType::NUM:
        this->operation_list.push_back(Operation{ OperationType::PUSH, node->value });
        break;

    default:
        break;
    }

    return this->operation_list;
}
