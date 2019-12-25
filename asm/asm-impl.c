#include "asm.h"
#include <string.h>
#include<stdio.h>
int64_t asm_add(int64_t a, int64_t b) {
  // TODO: implement
  asm(
    "movq %0, %%rax\n\t"
    "addq %1, %%rax\n\t"
    :"=a"(b)
    :"r"(a),"r"(b)
    "%%rax"
  );
  return b;
}

int asm_popcnt(uint64_t n) {
  // TODO: implement
  return 0;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  return NULL;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
