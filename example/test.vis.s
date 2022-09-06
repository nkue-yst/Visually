.intel_syntax noprefix
.global main

main:
  push 1
  push 2
  pop rax
  pop rdi
  add rax, rdi
  push rax
  push 2
  pop rax
  pop rdi
  imul rax, rdi
  push rax
  push 3
  pop rdi
  pop rax
  cqo
  idiv rdi
  push rax
  pop rax
  ret
