/**
 * @file    Variable.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/30
 */

#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <iostream>
#include <variant>
#include <string>

/* 変数情報を保管するクラス */
struct Variable
{
public:
    Variable(std::string name)
        : name(name)
        , value(nullptr)
    {}

    std::string name;    // 変数名

    std::variant<int32_t, std::nullptr_t> value;
};

static std::ostream& operator<<(std::ostream& stream, const Variable* var)
{
    stream << "name: "    << var->name << ", ";

    std::visit([&stream](const auto& value)
    {
        stream << "value: " << value;
    }, var->value);

    return stream;
}

#endif
