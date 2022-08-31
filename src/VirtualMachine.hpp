/**
 * @file    VirtualMachine.hpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#ifndef __VIRTUAL_MACHINE_HPP__
#define __VIRTUAL_MACHINE_HPP__

#include <cstdint>
#include <string>
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
    int32_t run(std::vector<struct Operation*>& operation_list, bool log_flag);

private:
    // 変数名から対応するポインタを検索
    struct Variable* findVariable(std::string name);

    // 未定義の変数を定義
    struct Variable* generateVariable(std::string name);

    // スタックに値を追加する
    void push(int32_t value);

    // スタックから値を取り出す
    int32_t pop();

    // レジスタ内のデータを出力
    void printReg() noexcept;

    // スタック内のデータを出力
    void printStack() noexcept;

    // 保持している変数一覧を出力
    void printVars() noexcept;

    // 値を保持するスタック
    int32_t stack[MAX_STACK_SIZE];

    // スタックポインタ
    int32_t* sp;

    // 変数を格納する
    std::vector<struct Variable*> var_list;

    // 変数一時読み出し用
    struct Variable* vp;

    // 計算等処理用レジスタ
    int32_t reg[static_cast<int32_t>(Register::REG_NUM)];

    // ログ出力フラグ
    bool log_flag;
};

#endif
