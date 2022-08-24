/**
 * @file    CodeGenerator.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__

#include "Operation.hpp"

#include <vector>

/* 命令コード生成器 */
class CodeGenerator
{
public:
    std::vector<Operation> generateCode(struct Node* node) noexcept;

private:
    std::vector<Operation> operation_list;
};

#endif
