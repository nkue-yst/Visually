/**
 * @file    Operation.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/31
 */

#include "Operation.hpp"

#include <iostream>

// 生成した命令列の出力処理
std::ostream& operator<<(std::ostream& stream, const Operation* op) noexcept
{
    switch (op->type)
    {
    case OperationType::PUSH:
        stream << "PUSH   (" << op->first_operand << ")";
        break;
    case OperationType::PUSH_R:
        stream << "PUSH_R (Reg_" << op->first_operand << ")";
        break;
    case OperationType::POP:
        stream << "POP    (Reg_" << op->first_operand << ")";
        break;
    case OperationType::READ:
        stream << "READ   (" << static_cast<const ReadOperation*>(op)->var_name << ")";
        break;
    case OperationType::LOAD:
        stream << "LOAD   (Reg_" << op->first_operand << ")";
        break;
    case OperationType::ADD:
        stream << "ADD    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::SUB:
        stream << "SUB    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::MUL:
        stream << "MUL    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::DIV:
        stream << "DIV    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::ASSIGN:
        stream << "ASSIGN";
        break;
    default:
        break;
    }

    return stream;
}
