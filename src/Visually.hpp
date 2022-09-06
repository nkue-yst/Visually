/**
 * @file    Visually.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/30
 */

#ifndef __VISUALLY_HPP__
#define __VISUALLY_HPP__

#include <cstdint>
#include <string>

extern std::string program_name;    // 読み込んだプログラム名

template<typename T, typename U>
T Cast(U value)
{
    return static_cast<T>(value);
}

template<typename T>
int32_t Int32(T value)
{
    return Cast<int32_t>(value);
}

#endif
