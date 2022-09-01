/**
 * @file    VirtualMachine.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "VirtualMachine.hpp"

#include <cstring>
#include <iostream>
#include <iomanip>

#include "Error.hpp"
#include "Operation.hpp"
#include "Variable.hpp"

#include <SDL.h>

VirtualMachine::VirtualMachine()
    : log_flag(false)
{
    this->sp = this->stack;    // スタックポインタは命令列用スタックの先頭を指す

    std::memset(this->stack, 0, sizeof(this->stack));

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

int32_t VirtualMachine::run(std::vector<struct Operation*>& operation_list, bool log_flag)
{
    this->log_flag = log_flag;
    if (this->log_flag)
    {
        std::cout << "---------- Running Log ----------" << std::endl;
    }

    std::vector<Operation*>::iterator op_iter = operation_list.begin();
    Operation* op = *op_iter;

    while (op_iter != operation_list.end())
    {
        /* ログ出力処理 */
        if (this->log_flag)
        {
            static uint32_t op_index = 0;

            std::cout << "[" << op_index++ << "]: " << op << std::endl;
        }

        /* 命令によって処理分岐 */
        switch (op->type)
        {
        case OperationType::PUSH:    // スタックへプッシュ
            this->push(op->first_operand);
            break;
        
        case OperationType::PUSH_R:
            this->push(this->reg[op->first_operand]);
            break;

        case OperationType::POP:    // スタックからポップ
            this->reg[op->first_operand] = pop();
            break;

        case OperationType::READ:    // 変数を一時読み出しポインタに読み出す
            this->vp = this->findVariable(static_cast<ReadOperation*>(op)->var_name);
            break;

        case OperationType::LOAD:
            this->reg[op->first_operand] = std::get<0>(this->vp->value);
            break;

        case OperationType::ADD:    // 加算演算
            this->push(this->reg[op->first_operand] + this->reg[op->second_operand]);
            break;

        case OperationType::SUB:    // 減算演算
            this->push(this->reg[op->first_operand] - this->reg[op->second_operand]);
            break;

        case OperationType::MUL:    // 乗算演算
            this->push(this->reg[op->first_operand] * this->reg[op->second_operand]);
            break;

        case OperationType::DIV:    // 除算演算
            this->push(this->reg[op->first_operand] / this->reg[op->second_operand]);
            break;

        case OperationType::ASSIGN:    // 代入演算
            this->vp->value = this->reg[0];
            break;

        case OperationType::RETURN:    // return文
            return this->reg[op->first_operand];

        default:
            break;
        }

        /* レジスタ&スタックの状態を出力 */
        if (this->log_flag)
        {
            this->printReg();
            this->printStack();
            this->printVars();
        }

        op = *(++op_iter);
    }

    if (this->log_flag)
    {
        std::cout << "---------------------------------" << std::endl << std::endl;
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

    if (this->log_flag)
        std::cout << "    " << "New-Variable => " << new_var << std::endl;

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

void VirtualMachine::printReg() noexcept
{
    uint32_t i = 0;

    std::cout << "\033[32m" << "    " << "[Register]" << "\033[m" << std::endl;

    for (int32_t value : this->reg)
    {
        std::cout << "      " << "<Reg_" << i++ << ">: " << value << std::endl;
    }
}

void VirtualMachine::printStack() noexcept
{
    std::cout << "\033[36m" << "    " << "[stack]" << "\033[m" << std::endl;

    int32_t* read_ptr = this->stack;
    for (int32_t value : this->stack)
    {
        if (read_ptr++ == this->sp + 1) break;

        std::cout << "    " << "|" << std::setw(5) << value << "|" << std::endl;
    }
}

void VirtualMachine::printVars() noexcept
{
    std::cout << "\033[35m" << "    " << "[variable]" << "\033[m" << std::endl;

    uint32_t index = 0;
    for (Variable* var : this->var_list)
    {
        std::cout << "      " << "(" << index++ << ") " << var << std::endl;
    }
}
