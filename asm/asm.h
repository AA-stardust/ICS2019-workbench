#include <stdint.h>
#include <unistd.h>

// TODO: set correct array length
typedef uint64_t asm_jmp_buf[8];
enum{rip,rbx,rcx,rdx,rsi,rdi,rbp,rsp};
int64_t asm_add(int64_t a, int64_t b);
int64_t asm_test(int64_t a,int64_t b);
int popcnt_test(uint64_t x);
int asm_popcnt(uint64_t n);
void *asm_memcpy(void *dest, const void *src, size_t n);
int asm_setjmp(asm_jmp_buf env);
void asm_longjmp(asm_jmp_buf env, int val);
void *memcpy_test(void *dest,const void *src,size_t n);