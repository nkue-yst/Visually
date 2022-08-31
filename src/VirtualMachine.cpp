/**
 * @file    VirtualMachine.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "VirtualMachine.hpp"

#include <iostream>

#include "Error.hpp"
#include "Operation.hpp"
#include "Variable.hpp"

#include <SDL.h>

VirtualMachine::VirtualMachine()
{
    this->sp = this->stack;    // スタックポインタは命令列用スタックの先頭を指す

    /* SDL関連の初期化処理 */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Error::setErrorMsg("failed to init sdl");
        Error::abort();
    }
}

VirtualMachine::~VirtualMachine()
{
    SDL_Quit();
}

int32_t VirtualMachine::run(std::vector<struct Operation*>& operation_list)
{
    std::vector<Operation*>::iterator op_iter = operation_list.begin();
    Operation* op = *op_iter;

    while (op_iter != operation_list.end())
    {
        switch (op->type)
        {
        case OperationType::PUSH:
            this->push(op->first_operand);
            break;

        case OperationType::POP:
            this->reg[op->first_operand] = pop();
            break;

        case OperationType::READ:
            this->vp = this->findVariable(static_cast<ReadOperation*>(op)->var_name);
            break;

        case OperationType::ADD:
            this->push(this->reg[op->first_operand] + this->reg[op->second_operand]);
            break;

        case OperationType::SUB:
            this->push(this->reg[op->first_operand] - this->reg[op->second_operand]);
            break;

        case OperationType::MUL:
            this->push(this->reg[op->first_operand] * this->reg[op->second_operand]);
            break;

        case OperationType::DIV:
            this->push(this->reg[op->first_operand] / this->reg[op->second_operand]);
            break;

        case OperationType::ASSIGN:
            this->vp->value = this->reg[0];
            break;

        default:
            break;
        }

        op = *(++op_iter);
    }

    return this->pop();    // スタックのトップを実行結果として返す
}

Variable* VirtualMachine::findVariable(std::string name)
{
    for (Variable* var : this->var_list)
    {
        if (var->name == name)
        {
            return var;
        }
    }
    
    return this->generateVariable(name);
}

Variable* VirtualMachine::generateVariable(std::string name)
{
    Variable* new_var = new Variable(name);
    this->var_list.push_back(new_var);

    return new_var;
}

void VirtualMachine::push(int32_t value)
{
    *(++sp) = value;
}

int32_t VirtualMachine::pop()
{
    return *(sp--);
}
