/**
 * @file    main.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"
#include "Error.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "TextInput.hpp"
#include "Token.hpp"
#include "VirtualMachine.hpp"

#include <iostream>
#include <fstream>
#include <vector>

constexpr char version[] = "0.0.1";

void printHelp(const char* exec_command)
{
    std::cerr << "Visually version " << version << std::endl;
    std::cerr << "Usage: " << exec_command << " [options] input" << std::endl;
    std::cerr << "Options:\n"
                << "    " << "-t" << "    Output token info\n"
                << std::endl;
}

int main(int argc, char** argv)
{
    bool token_flag = false;    // トークン情報出力フラグ

    CodeGenerator code_generator;    // 命令列生成器
    Parser parser;                   // プログラム解析器
    TextInput text_input;            // ソースプログラム読み込みクラス
    VirtualMachine vm;               // 実行用仮想マシン

    int32_t ac = 1;    // コマンドライン引数走査カウンタ

    /* オプションの解析 */
    while (ac < argc)
    {
        if (argv[ac][0] == '-')
        {
            switch (argv[ac][1])
            {
            case 't':
                token_flag = true;
                break;

            case 'h':
                printHelp(argv[0]);
                return 0;

            default:
                printHelp(argv[0]);
                return 1; 
            }
        }
        else
        {
            break;
        }

        ac++;
    }

    if (ac >= argc)    // オプション以外に引数が無い場合エラー
    {
        Error::setErrorMsg("no source");
        Error::abort();
    }

    text_input.openFile(argv[ac]);    // ソースプログラムを開く

    /* プログラムをトークンに変換 */
    std::vector<Token*> token_list;
    token_list = Token::strToToken(text_input.getNewLine());

    /* 変換されたトークンの一覧を出力 */
    if (token_flag)
    {
        std::cout << "---------- Token Info ----------" << std::endl;

        for (Token* token : token_list)
        {
            std::cout << token << std::endl;

            if (token != token_list.back())
                std::cout << std::endl;
        }

        std::cout << "--------------------------------" << std::endl << std::endl;
    }

    Node* node = parser.parse(token_list);    // トークンから構文解析を行う

    std::vector<Operation> code_list = code_generator.generateCode(node);    // 実行用コードを生成

    std::cout << vm.run(code_list) << std::endl;    // 命令列を実行（実行結果を出力）

    delete node;
    for (auto token : token_list)
        delete token;
}
