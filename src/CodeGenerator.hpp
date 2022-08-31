/**
 * @file    CodeGenerator.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__

#include "Operation.hpp"

#include <string>
#include <vector>

/* 命令コード生成器 */
class CodeGenerator
{
public:
    CodeGenerator() noexcept;

    std::vector<Operation*> generateCode(std::vector<struct Node*> node_list) noexcept;

private:
    void generate(struct Node* node) noexcept;

    // 変数を作成する
    void generateVariable(std::string name) noexcept;

    // 変数が既に存在するか検索する
    void findVariable(std::string name) noexcept;

    std::vector<struct Variable*> var_list;

    std::vector<Operation*> operation_list;
};

#endif
