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
int popcnt_test(uint64_t x){
  int s = 0;
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }
  return s;
}
int asm_popcnt(uint64_t n) {
  asm volatile(
    "xor %%ecx,%%ecx\n\t"//记录i
    "xor %%eax,%%eax\n\t"//记录返回值
    "nopl 0x0(%%rax)\n\t"
    "movq %%rdi,%%rdx\n\t"
    "shrq %%cl,%%rdx\n\t"
    "addl $0x1,%%ecx\n\t"
    "andl $0x1,%%edx\n\t"
    "addl %%edx,%%eax\n\t"
    "cmpl $0x40,%%ecx\n\t"
    "jne asm_popcnt+0x7\n\t"
    "movq %%rax,%0\n\t"
    :"=g"(n)
    :
    :"ecx","eax","rdi","rdx"
  );
  return n;
}
void *memcpy_test(void *dest,const void *src,size_t n){
  if(!(dest && src)) return 0;
   void *out0=dest;
   while(n){ 
     *(char *)dest=*(char *)src;
     dest++;
     src++;
     n--;
   }
   return out0;
}
void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  //return NULL;
  asm(
    "test %%rdi,%%rdi\n\t"
    "je memcpy_test+47\n\t"
    "test %%rsi,%%rsi\n\t"
    "je memcpy_test+47\n\t"
    "xor %%ecx,%%ecx\n\t"
    "test %%rdx,%%rdx\n\t"
    "je memcpy_test+38\n\t"
    "movzbl (%%rsi,%%rcx,1),%%r8d\n\t"
    "mov %%r8b,(%%rdi,%%rcx,1)\n\t"
    "addq $0x1,%%rcx\n\t"
    "cmp %%rcx,%%rdx\n\t"
    "jne memcpy_test+24\n\t"
    "movq %%rdi,%%rax\n\t"
    "movq %%rax,%0\n\t"
    "retq\n\t"   
    "xchg %%ax,%%ax\n\t"
    "xor %%eax,%%eax\n\t"
    "movq %%rax,%0\n\t"
    "retq\n\t"   
    :"=g"(dest)
    :
    :"rdi","rsi","ecx","rax"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  //register uint64_t rip0 asm("rbx")=0;
  asm(
    "movq (%%rsp),%%rax\n\t"
    "movq %%rax,(%0)\n\t"
    "movq %%rbx,0x8(%0)\n\t"
    "movq %%rcx,0x10(%0)\n\t"
    "movq %%rdx,0x18(%0)\n\t"
    "movq %%rsi,0x20(%0)\n\t"
    "movq %%rdi,0x28(%0)\n\t"
    "movq %%rbp,0x30(%0)\n\t"
    "movq %%rsp,%%rax\n\t"
    "addq $0x8,%%rax\n\t"
    "movq %%rax,0x38(%0)\n\t"
    :
    :"r"(env)
    :"rax"
  );
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
  asm(
    "movq 0x8(%0),%%rbx\n\t"
    "movq 0x10(%0),%%rcx\n\t"
    "movq 0x18(%0),%%rdx\n\t"
    "movq 0x20(%0),%%rsi\n\t"
    "movq 0x28(%0),%%rdi\n\t"
    "movq 0x30(%0),%%rbp\n\t"
    "movq 0x38(%0),%%rsp\n\t"
    "movq %0,%%rdi\n\t"
    "movl %1,%%eax\n\t"
    "jmp *(%%rdi)\n\t"
    :
    :"a"(env),"r"(val)
    :"rbx","rcx","rdx","rsi","rdi","rsp","rbp"
  );

}
