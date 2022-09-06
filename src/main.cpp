/**
 * @file    main.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "Assembler.hpp"
#include "CodeGenerator.hpp"
#include "Error.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "TextInput.hpp"
#include "Token.hpp"
#include "VirtualMachine.hpp"

#include <chrono>
#include <iomanip>
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

    Assembler assembler;             // アセンブラ
    CodeGenerator code_generator;    // 命令列生成器
    Parser parser;                   // プログラム解析器
    TextInput text_input;            // ソースプログラム読み込みクラス
    VirtualMachine vm;               // 実行用仮想マシン

    std::chrono::system_clock::time_point tp_start, tp_end;    // 処理時間計測用
    double dur_tokenize, dur_parsing, dur_code_generating, dur_running;    // 計測した処理時間を格納する

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

    program_name = argv[ac];
    text_input.openFile(program_name.c_str());    // ソースプログラムを開く

    /* プログラムをトークンに変換 */
    tp_start = std::chrono::system_clock::now();
    std::vector<Token*> token_list;
    std::string file_contents = std::string(std::istreambuf_iterator<char>(text_input.fs), std::istreambuf_iterator<char>());
    token_list = Token::strToToken(file_contents.c_str());
    tp_end = std::chrono::system_clock::now();
    dur_tokenize = std::chrono::duration_cast<std::chrono::microseconds>(tp_end - tp_start).count();

    /* 生成されたトークン一覧を出力 */
    if (token_flag)
    {
        std::cout << "---------- Token Info ----------" << std::endl;
        for (Token* token : token_list)
            std::cout << token << std::endl << std::endl;
        std::cout << "\e[1A" << "--------------------------------" << std::endl << std::endl;
    }

    /* トークンから構文解析を行う（構文木のルートノードを取得） */
    tp_start = std::chrono::system_clock::now();
    std::vector<Node*> node_list = parser.parse(token_list);
    tp_end = std::chrono::system_clock::now();
    dur_parsing = std::chrono::duration_cast<std::chrono::microseconds>(tp_end - tp_start).count();

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

    /* アセンブリを出力 */
    assembler.generateAssembly(node_list);

    /* 実行用コードを生成 */
    tp_start = std::chrono::system_clock::now();
    std::vector<Operation*> code_list = code_generator.generateCode(node_list);
    tp_end = std::chrono::system_clock::now();
    dur_code_generating = std::chrono::duration_cast<std::chrono::microseconds>(tp_end - tp_start).count();

    /* 生成された命令列を出力 */
    if (code_flag)
    {
        uint32_t code_index = 0;

        std::cout << "---------- Code Info ----------" << std::endl;

        for (Operation* op : code_list)
        {
            std::cout << "[" << std::setw(2) << code_index++ << "]: " << op << std::endl;
        }

        std::cout << "-------------------------------" << std::endl << std::endl;
    }

    /* 命令列を実行 */
    tp_start = std::chrono::system_clock::now();
    int32_t return_code = vm.run(code_list, log_flag);
    tp_end = std::chrono::system_clock::now();
    dur_running = std::chrono::duration_cast<std::chrono::microseconds>(tp_end - tp_start).count();

    for (auto code : code_list)   delete code;     // 生成した命令列の破棄
    for (auto node : node_list)   delete node;     // 生成したノードの破棄
    for (auto token : token_list) delete token;    // 生成したトークンの破棄

    /* 処理時間の出力 */
    std::cout << "------------------------" << std::endl;
    std::cout << "Tokenize:      " << std::setw(3) << dur_tokenize        << " μs" << std::endl;
    std::cout << "Parse:         " << std::setw(3) << dur_parsing         << " μs" << std::endl;
    std::cout << "Code Generate: " << std::setw(3) << dur_code_generating << " μs" << std::endl;
    std::cout << "Run:           " << std::setw(3) << dur_running         << " μs" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << "Return code: " << return_code << std::endl;
    return return_code;
}
