/**
 * @file    VirtualMachine.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __VIRTUAL_MACHINE_HPP__
#define __VIRTUAL_MACHINE_HPP__

#include <cstdint>
#include <vector>

// スタックのサイズを定義
constexpr uint32_t MAX_STACK_SIZE = 1024;

enum class Register
{
    REG_0,
    REG_1,
    REG_NUM,    // レジスタの総数
};

class VirtualMachine
{
public:
    VirtualMachine();
    ~VirtualMachine();

    // プログラムを実行する
    int32_t run(std::vector<struct Operation*>& operation_list);

private:
    // スタックに値を追加する
    void push(int32_t value);

    // スタックから値を取り出す
    int32_t pop();

    // 命令列を入力するスタック
    int32_t stack[MAX_STACK_SIZE];

    // スタックポインタ
    int32_t* sp;

    // 計算等処理用レジスタ
    int32_t reg[static_cast<int32_t>(Register::REG_NUM)];
};

#endif
