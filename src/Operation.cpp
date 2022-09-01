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
    using enum OperationType;

    switch (op->type)
    {
    case PUSH:
        stream << "PUSH   (" << op->first_operand << ")";
        break;
    case PUSH_R:
        stream << "PUSH_R (Reg_" << op->first_operand << ")";
        break;
    case POP:
        stream << "POP    (Reg_" << op->first_operand << ")";
        break;
    case READ:
        stream << "READ   (" << static_cast<const ReadOperation*>(op)->var_name << ")";
        break;
    case LOAD:
        stream << "LOAD   (Reg_" << op->first_operand << ")";
        break;
    case ADD:
        stream << "ADD    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case SUB:
        stream << "SUB    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case MUL:
        stream << "MUL    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case DIV:
        stream << "DIV    (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case ASSIGN:
        stream << "ASSIGN";
        break;
    case EQUAL:
        stream << "EQUAL";
        break;
    case NEQUAL:
        stream << "NEQUAL";
        break;
    case LESS:
        stream << "LESS";
        break;
    case GREATER:
        stream << "GREATER";
        break;
    case LESSEQ:
        stream << "LESSEQ";
        break;
    case GREATEREQ:
        stream << "GREATEREQ";
        break;
    case RETURN:
        stream << "RETURN (Reg_" << op->first_operand << ")";
        break;
    default:
        break;
    }

    return stream;
}
