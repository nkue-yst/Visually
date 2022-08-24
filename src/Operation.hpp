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
    UNDEFINED,
};

/* 命令列の定義 */
struct Operation
{
public:
    Operation() noexcept
        : type(OperationType::UNDEFINED)
        , operand(0)
    {}

    Operation(OperationType type, int32_t operand) noexcept
        : type(type)
        , operand(operand)
    {}

    OperationType type;
    int32_t operand;
};

#endif
