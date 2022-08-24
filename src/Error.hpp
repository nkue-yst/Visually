/**
 * @file    Error.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <string>

/* エラーメッセージ関連クラス */
namespace Error
{

    // セットされているエラーメッセージを出力し異常終了させる
    void abort() noexcept;

    // 'key'に対応したエラーメッセージをセットする
    void setErrorMsg(std::string key);

    namespace
    {
        // 最近発生したエラーに対するメッセージ
        std::string msg;
    }

};

#endif
