#include "asm.h"
#include <string.h>
#include<stdio.h>
int64_t asm_test(int64_t a,int64_t b){
  return a+b;
}
int64_t asm_add(int64_t a, int64_t b) {
  // TODO: implement
  //int64_t c;
  asm volatile(
    "movq %1, %%rax\n\t"
    "addq %2, %%rax\n\t"
    "movq %%rax,%0\n\t"
    :"=g"(b)
    :"r"(a),"r"(b)
    :"%rax"
  );
  return b;
}
int popcnt_test(uint64_t n){
  int s = 0;
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }
  return s;
}
int asm_popcnt(uint64_t n) {
  asm volatile(

  );
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
