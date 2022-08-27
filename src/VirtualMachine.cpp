/**
 * @file    VirtualMachine.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "VirtualMachine.hpp"
#include "Error.hpp"
#include "Operation.hpp"

#include <SDL.h>

#include <iostream>

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

int32_t VirtualMachine::run(std::vector<struct Operation>& operation_list)
{
    std::vector<Operation>::iterator operation = operation_list.begin();

    while (operation != operation_list.end())
    {
        switch (operation->type)
        {
        case OperationType::PUSH:
            this->push(operation->first_operand);
            break;

        case OperationType::POP:
            this->reg[operation->first_operand] = pop();
            break;

        case OperationType::ADD:
            this->push(this->reg[operation->first_operand] + this->reg[operation->second_operand]);
            break;

        case OperationType::SUB:
            this->push(this->reg[operation->first_operand] - this->reg[operation->second_operand]);
            break;

        case OperationType::MUL:
            this->push(this->reg[operation->first_operand] * this->reg[operation->second_operand]);
            break;

        case OperationType::DIV:
            this->push(this->reg[operation->first_operand] / this->reg[operation->second_operand]);
            break;

        default:
            break;
        }

        operation++;
    }

    return pop();    // スタックのトップを実行結果とする
}

void VirtualMachine::push(int32_t value)
{
    *(++sp) = value;
}

int32_t VirtualMachine::pop()
{
    return *(sp--);
}
