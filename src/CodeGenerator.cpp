/**
 * @file    CodeGenerator.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"

#include "Node.hpp"
#include "Variable.hpp"
#include "VirtualMachine.hpp"
#include "Visually.hpp"

CodeGenerator::CodeGenerator() noexcept
{}

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
    using enum OperationType;

    switch (node->type)
    {
    case NodeType::NUM:
        this->operation_list.push_back(new Operation(PUSH, node->value));
        break;

    case NodeType::ADD:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_0)));
        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_1)));
        this->operation_list.push_back(new Operation(ADD, Int32(Register::REG_0), Int32(Register::REG_1)));
        break;

    case NodeType::SUB:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_0)));
        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_1)));
        this->operation_list.push_back(new Operation(SUB, Int32(Register::REG_1), Int32(Register::REG_0)));
        break;

    case NodeType::MUL:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_0)));
        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_1)));
        this->operation_list.push_back(new Operation(MUL, Int32(Register::REG_0), Int32(Register::REG_1)));
        break;

    case NodeType::DIV:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_0)));
        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_1)));
        this->operation_list.push_back(new Operation(MUL, Int32(Register::REG_1), Int32(Register::REG_0)));
        break;

    case NodeType::ASSIGN:
        this->generate(node->left);
        this->generate(node->right);

        this->operation_list.push_back(new Operation(POP, Int32(Register::REG_0)));
        this->operation_list.push_back(new Operation(ASSIGN));
        break;

    case NodeType::IDENTIFIER:
        this->findVariable(node->var_name);
        this->operation_list.push_back(new ReadOperation(node->var_name));
        break;

    default:
        break;
    }
}

void CodeGenerator::findVariable(std::string name) noexcept
{
    for (Variable* var : this->var_list)
    {
        if (var->name == name)
        {
            return;
        }
    }
    
    this->generateVariable(name);
}

void CodeGenerator::generateVariable(std::string name) noexcept
{
    this->var_list.push_back(new Variable(name));
}
