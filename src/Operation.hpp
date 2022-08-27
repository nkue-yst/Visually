/**
 * @file    Operation.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __OPERATION_HPP__
#define __OPERATION_HPP__

#include <cstdint>
#include <iostream>
#include <string>

/* 命令コードの種類 */
enum class OperationType
{
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    UNDEFINED,
};

/* 命令列の定義 */
struct Operation
{
public:
    Operation() noexcept
        : type(OperationType::UNDEFINED)
        , first_operand(0)
        , second_operand(0)
    {}

    Operation(OperationType type, int32_t first_operand, int32_t second_operand = 0) noexcept
        : type(type)
        , first_operand(first_operand)
        , second_operand(second_operand)
    {}

    OperationType type;

    int32_t first_operand;
    int32_t second_operand;
};

// 生成した命令列の出力処理
static std::ostream& operator<<(std::ostream& stream, const Operation* op)
{
    switch (op->type)
    {
    case OperationType::PUSH:
        stream << "PUSH (" << op->first_operand << ")";
        break;
    case OperationType::POP:
        stream << "POP  (Reg_" << op->first_operand << ")";
        break;
    case OperationType::ADD:
        stream << "ADD  (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::SUB:
        stream << "SUB  (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::MUL:
        stream << "MUL  (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    case OperationType::DIV:
        stream << "DIV  (Reg_" << op->first_operand << ", Reg_" << op->second_operand << ")";
        break;
    default:
        break;
    }

    return stream;
}

#endif
