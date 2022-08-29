/**
 * @file    TextInput.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "TextInput.hpp"
#include "Error.hpp"

#include <iostream>

constexpr int32_t BUFF_SIZE = 512;

TextInput::TextInput() noexcept
    : lines(0)
{}

void TextInput::openFile(const char* file_name)
{
    this->fs = std::ifstream(file_name);

    if (this->fs.fail())
    {
        Error::setErrorMsg("cannot open source");
        Error::abort();
    }
}
