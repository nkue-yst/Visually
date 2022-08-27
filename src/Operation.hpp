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
    std::string type;

    switch (op->type)
    {
    case OperationType::PUSH:
        type = "PUSH";
        break;
    case OperationType::POP:
        type = "POP";
        break;
    case OperationType::ADD:
        type = "ADD";
        break;
    case OperationType::SUB:
        type = "SUB";
        break;
    case OperationType::MUL:
        type = "MUL";
        break;
    case OperationType::DIV:
        type = "DIV";
        break;
    default:
        break;
    }

    stream << type;

    return stream;
}

#endif
