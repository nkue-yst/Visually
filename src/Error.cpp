/**
 * @file    Error.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "Error.hpp"

#include <iostream>
#include <unordered_map>

namespace Error
{

    std::unordered_map<std::string, std::string> msg_table = {
        { "undefined error",    "予期せぬエラーが発生しました" },
        { "no source",          "ソースプログラムを指定してください" },
        { "cannot open source", "ソースプログラムが開けませんでした" },
        { "invalid char",       "不正な文字が含まれています" },
    };

    void abort() noexcept
    {
        std::cerr << "plc: " << "\033[1;31m" << "fatal error: " << "\033[m" << msg << std::endl;
        exit(1);
    }

    void setErrorMsg(std::string key)
    {
        try
        {
            msg = msg_table.at(key);
        }
        catch (std::out_of_range& e)
        {
            setErrorMsg("undefined error");
        }
    }

}
