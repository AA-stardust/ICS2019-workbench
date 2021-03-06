#include "asm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void setjmp_test0();
static void setjmp_test1();

int main() {
  // TODO: add more tests here!
  assert(asm_add(1, 2) == 3);
  assert(asm_add(0x12,0x23)==0x35);
  int64_t temp1=asm_test(0xffffffffffff,0xfabcdfffffff);
  int64_t temp2=asm_add(0xffffffffffff,0xfabcdfffffff);
  assert(temp2==temp1);
  assert(asm_popcnt(0xffffffffffffffffull) == 64);
   
  // TODO: add memcpy tests here!
  char a[20];
  const char b[]="ljk jia you,you hen hao";
  asm_memcpy(a,b,15);
  a[15]='\0';
  //printf("%s\n",a);
  assert(asm_memcpy(NULL, NULL, 0) == NULL);
  
  // setjmp test starts here
  setjmp_test0();
  setjmp_test1();
  printf("PASS!\n");
  return 0;
}

struct log_entry {
  const char *str;
  int value;
};
static asm_jmp_buf bufferA, bufferB;
static struct log_entry expected[] = {
  // expected output sequence for setjmp tests
  { "A", 0 },
  { "B", 999 },
  { "A1", 0 },
  { "B1", 0 },
  { "A2", 10001 },
  { "B2", 20001 },
  { "A3", 10002 },
  { "B3", 20002 },
  { "A4", 10003 },
  { NULL, 0 },
};
static struct log_entry *head = expected;

static void setjmp_log(const char *str, int value) {
  assert(head->str != NULL);
  assert(strcmp(head->str, str) == 0);
  assert(head->value == value);
  head++;
}

static void setjmp_test2();
static void setjmp_test1() {
  int r = 0;
  setjmp_log("A1", r);
  printf("A1\n");
  if ((r = asm_setjmp(bufferA)) == 0) {
    setjmp_test2();
  }
  setjmp_log("A2", r);
  printf("A2\n");
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20001);
  }
  setjmp_log("A3", r);
  printf("A3\n");
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20002);
  }
  setjmp_log("A4", r);
  printf("A4\n");
  assert(head->str == NULL);
}

static void setjmp_test2() {
  int r = 0;
  setjmp_log("B1", r);
  printf("B1\n");
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10001);
  }
  setjmp_log("B2", r);
  printf("B2\n");
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10002);
  }
  setjmp_log("B3", r);
  printf("B3\n");
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10003);
  }
}

static asm_jmp_buf buf;

static void setjmp_test_simple() {
  asm_longjmp(buf, 999);
}

static void setjmp_test0() {
  int r;
  if ((r = asm_setjmp(buf)) == 0) {
    setjmp_log("A", r);
    printf("A\n");
    setjmp_test_simple();
  }
  setjmp_log("B", r);
  printf("B\n");
}
