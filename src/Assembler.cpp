/**
 * @file    Assembler.hpp
 * @author  Yoshito Nakaue
 * @date    2022/09/02
 */

#include "Assembler.hpp"

#include <iostream>
#include <string>

#include "Node.hpp"
#include "Visually.hpp"

const char* TAB = "    ";

std::string program_name;

using std::endl;

void Assembler::generateAssembly(std::vector<Node*> node_list)
{
    this->assembly = std::ofstream(program_name + ".s");

    this->assembly
        << ".intel_syntax noprefix" << endl
        << ".global main"           << endl
        << endl
        << "main:"                  << endl;

    for (Node* node : node_list)
    {
        this->generate(node);
    }

    this->assembly << "  pop rax" << endl;
    this->assembly << "  ret"     << endl;

    this->assembly.close();
}

void Assembler::generate(Node* node)
{
    using enum NodeType;

    switch (node->type)
    {
    case NUM:
        this->assembly << "  push " << node->value << endl;
        break;

    case ADD:
        this->generate(node->left);
        this->generate(node->right);

        this->assembly << "  pop rax"      << endl;
        this->assembly << "  pop rdi"      << endl;
        this->assembly << "  add rax, rdi" << endl;
        this->assembly << "  push rax"     << endl;
        break;

    case SUB:
        this->generate(node->left);
        this->generate(node->right);

        this->assembly << "  pop rdi"      << endl;
        this->assembly << "  pop rax"      << endl;
        this->assembly << "  sub rax, rdi" << endl;
        this->assembly << "  push rax"     << endl;
        break;
    
    case MUL:
        this->generate(node->left);
        this->generate(node->right);

        this->assembly << "  pop rax"       << endl;
        this->assembly << "  pop rdi"       << endl;
        this->assembly << "  imul rax, rdi" << endl;
        this->assembly << "  push rax"      << endl;
        break;
    
    case DIV:
        this->generate(node->left);
        this->generate(node->right);

        this->assembly << "  pop rdi"  << endl;
        this->assembly << "  pop rax"  << endl;
        this->assembly << "  cqo"      << endl;
        this->assembly << "  idiv rdi" << endl;
        this->assembly << "  push rax" << endl;
        break;

    case ASSIGN:
        break;

    case EQUAL:
        break;

    case NEQUAL:
        break;

    case LESS:
        break;

    case GREATER:
        break;

    case LESSEQ:
        break;

    case GREATEREQ:
        break;

    case IDENTIFIER:
        break;

    case RETURN:
        break;

    case ID_VAR:
        break;

    case UNDIFINED:
    default:
        break;    
    }
}
