/**
 * @file    Assembler.hpp
 * @author  Yoshito Nakaue
 * @date    2022/09/02
 */

#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include <fstream>
#include <vector>

class Assembler
{
public:
    void generateAssembly(std::vector<struct Node*> node_list);

private:
    void generate(Node* node);

    std::ofstream assembly;
};

#endif
