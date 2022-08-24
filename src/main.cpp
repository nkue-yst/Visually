/**
 * @file    main.cpp
 * @author  Yoshito Nakaue
 * @date    2022/08/25
 */

#include "CodeGenerator.hpp"
#include "Error.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Token.hpp"
#include "VirtualMachine.hpp"

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    CodeGenerator code_generator;
    Parser parser;
    VirtualMachine vm;

    if (argc < 2)
    {
        Error::setErrorMsg("no source");
        Error::abort();
    }

    std::vector<Token> token_list = Token::strToToken(argv[1]);    // プログラムをトークンに変換

    Node* node = parser.parse(token_list);    // トークンから構文解析を行う

    std::vector<Operation> code_list = code_generator.generateCode(node);    // 実行用コードを生成

    std::cout << vm.run(code_list) << std::endl;    // 命令列を実行（実行結果を出力）
}
