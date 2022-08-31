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
                << "    " << "-t" << "    Output read token list\n"
                << "    " << "-n" << "    Output parsing node list\n"
                << "    " << "-c" << "    Output generated code list\n"
                << "    " << "-v" << "    Output virtual machine running log\n"
                << std::endl;
}

int main(int argc, char** argv)
{
    bool token_flag = false;    // トークン情報出力フラグ
    bool node_flag  = false;    // ノード情報出力フラグ
    bool code_flag  = false;    // 命令列出力フラグ
    bool log_flag   = false;    // 実行時

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
            case 'n':
                node_flag = true;
                break;
            case 'c':
                code_flag = true;
                break;
            case 'v':
                log_flag = true;
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
    std::string file_contents = std::string(std::istreambuf_iterator<char>(text_input.fs), std::istreambuf_iterator<char>());
    token_list = Token::strToToken(file_contents.c_str());

    /* 生成されたトークン一覧を出力 */
    if (token_flag)
    {
        std::cout << "---------- Token Info ----------" << std::endl;
        for (Token* token : token_list)
            std::cout << token << std::endl << std::endl;
        std::cout << "\e[1A" << "--------------------------------" << std::endl << std::endl;
    }

    /* トークンから構文解析を行う（構文木のルートノードを取得） */
    std::vector<Node*> node_list = parser.parse(token_list);

    /* 生成されたノード一覧を出力 */
    if (node_flag)
    {
        std::cout << "---------- Node Info ----------" << std::endl;

        for (Node* node : node_list)
        {
            uint32_t depth = 0;
            static uint32_t node_num = 1;

            std::cout << "--- <Node " << node_num++ << "> ---" << std::endl;

            std::cout << node << std::endl;    // ルートノードを出力
            std::cout << "depth: " << depth++ << std::endl << std::endl;

            node->printChildren(depth);    // ルートノードから再帰的に全ノード情報を出力
        }

        std::cout << "\e[1A" << "-------------------------------" << std::endl << std::endl;
    }

    std::vector<Operation*> code_list = code_generator.generateCode(node_list);    // 実行用コードを生成

    /* 生成された命令列を出力 */
    if (code_flag)
    {
        uint32_t code_index = 0;

        std::cout << "---------- Code Info ----------" << std::endl;

        for (Operation* op : code_list)
        {
            std::cout << "[" << code_index++ << "]: " << op << std::endl;
        }

        std::cout << "-------------------------------" << std::endl << std::endl;
    }

    std::cout << vm.run(code_list, log_flag) << std::endl;    // 命令列を実行（実行結果を出力）

    for (auto code : code_list)   delete code;     // 生成した命令列の破棄
    for (auto node : node_list)   delete node;     // 生成したノードの破棄
    for (auto token : token_list) delete token;    // 生成したトークンの破棄
}
