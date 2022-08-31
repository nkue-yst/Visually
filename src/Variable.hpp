/**
 * @file    Variable.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/30
 */

#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <any>
#include <string>

/* 変数情報を保管するクラス */
struct Variable
{
public:
    Variable(std::string name)
        : name(name)
    {}

    std::string name;    // 変数名

    std::any value;
};

#endif
