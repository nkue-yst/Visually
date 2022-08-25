/**
 * @file    TextInput.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __TEXT_INPUT_HPP__
#define __TEXT_INPUT_HPP__

#include <fstream>
#include <string>

/* ソースプログラムファイルから文字列を読み込むクラス */
class TextInput
{
public:
    TextInput() noexcept;

    // ファイルを開く
    void openFile(const char* file_name);

    std::string getNewLine();

private:
    // 入力ファイルストリーム
    std::ifstream fs;

    // 読み込んだ行数
    uint32_t lines;
};

#endif
