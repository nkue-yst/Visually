/**
 * @file    Operation.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __OPERATION_HPP__
#define __OPERATION_HPP__

#include <cstdint>

/* 命令コードの種類 */
enum class OperationType
{
    PUSH,
    POP,
    ADD,
    SUB,
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

#endif
