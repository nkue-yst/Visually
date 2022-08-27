/**
 * @file    CodeGenerator.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"
#include "Node.hpp"
#include "VirtualMachine.hpp"

std::vector<Operation> CodeGenerator::generateCode(Node* node) noexcept
{
    switch (node->type)
    {
    case NodeType::NUM:
        this->operation_list.push_back(Operation(OperationType::PUSH, node->value));
        break;

    case NodeType::ADD:
        this->generateCode(node->left);
        this->generateCode(node->right);

        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(Operation(OperationType::ADD, static_cast<int32_t>(Register::REG_0), static_cast<int32_t>(Register::REG_1)));
        break;

    case NodeType::SUB:
        this->generateCode(node->left);
        this->generateCode(node->right);

        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(Operation(OperationType::SUB, static_cast<int32_t>(Register::REG_1), static_cast<int32_t>(Register::REG_0)));
        break;

    case NodeType::MUL:
        this->generateCode(node->left);
        this->generateCode(node->right);

        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(Operation(OperationType::MUL, static_cast<int32_t>(Register::REG_0), static_cast<int32_t>(Register::REG_1)));
        break;

    case NodeType::DIV:
        this->generateCode(node->left);
        this->generateCode(node->right);

        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(Operation(OperationType::MUL, static_cast<int32_t>(Register::REG_1), static_cast<int32_t>(Register::REG_0)));
        break;

    default:
        break;
    }

    return this->operation_list;
}
