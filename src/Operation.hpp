/**
 * @file    Operation.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __OPERATION_HPP__
#define __OPERATION_HPP__

#include <cstdint>
#include <iosfwd>
#include <string>

#include "VirtualMachine.hpp"
#include "Visually.hpp"

/* 命令コードの種類 */
enum class OperationType
{
    PUSH, PUSH_R, POP,
    READ, LOAD,
    ADD,  SUB, MUL, DIV,
    ASSIGN,
    EQUAL, NEQUAL,
    LESS, GREATER, LESSEQ, GREATEREQ,
    RETURN,
    UNDEFINED,
};

/* 命令列ベースの定義 */
struct Operation
{
public:
    Operation() noexcept
        : type(OperationType::UNDEFINED)
        , first_operand(0)
        , second_operand(0)
    {}

    Operation(OperationType type, int32_t first_operand = 0, int32_t second_operand = 0) noexcept
        : type(type)
        , first_operand(first_operand)
        , second_operand(second_operand)
    {}

    Operation(OperationType type, Register first_operand, Register second_operand = Register::REG_0)
        : type(type)
        , first_operand(Int32(first_operand))
        , second_operand(Int32(second_operand))
    {}

    OperationType type;

    int32_t first_operand;
    int32_t second_operand;
};

/* 変数アドレスの読み込み命令列の定義 */
struct ReadOperation : public Operation
{
public:
    ReadOperation(std::string var_name) noexcept
        : Operation(OperationType::READ)
        , var_name(var_name)
    {}

    std::string var_name;
};

std::ostream& operator<<(std::ostream& stream, const Operation* op) noexcept;

#endif
