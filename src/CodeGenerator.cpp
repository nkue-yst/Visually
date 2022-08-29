/**
 * @file    CodeGenerator.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"
#include "Node.hpp"
#include "VirtualMachine.hpp"

std::vector<Operation*> CodeGenerator::generateCode(std::vector<Node*> node_list) noexcept
{
    for (Node* node : node_list)
    {
        this->generate(node);
    }

    return this->operation_list;
}

void CodeGenerator::generate(Node* node) noexcept
{
    switch (node->type)
    {
    case NodeType::NUM:
        this->operation_list.push_back(new Operation(OperationType::PUSH, node->value));
        break;

    case NodeType::ADD:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(new Operation(OperationType::ADD, static_cast<int32_t>(Register::REG_0), static_cast<int32_t>(Register::REG_1)));
        break;

    case NodeType::SUB:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(new Operation(OperationType::SUB, static_cast<int32_t>(Register::REG_1), static_cast<int32_t>(Register::REG_0)));
        break;

    case NodeType::MUL:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(new Operation(OperationType::MUL, static_cast<int32_t>(Register::REG_0), static_cast<int32_t>(Register::REG_1)));
        break;

    case NodeType::DIV:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_0)));
        this->operation_list.push_back(new Operation(OperationType::POP, static_cast<int32_t>(Register::REG_1)));
        this->operation_list.push_back(new Operation(OperationType::MUL, static_cast<int32_t>(Register::REG_1), static_cast<int32_t>(Register::REG_0)));
        break;

    default:
        break;
    }
}
