#include "multimod.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
_Bool mul_exeed(int64_t a,int64_t b){
  volatile int64_t c=a*b;
  printf("exeed: c=%ld\n",c);
  printf("exeed: a=%ld\n",a);
  printf("exeed: b=%ld\n",b);
  printf("exeed: c/b=%ld\n",c/b);
  return !(b==0||a==c/b);
}
int64_t add_mod(int64_t a,int64_t b,int64_t m){
  uint64_t a1=a+b;
  uint64_t result=a1%(uint64_t)m;
  if((int64_t)result<0){
    printf("a:%lx b:%lx m:%lx result:%lx\n",a,b,m,result);
  }
  //printf("a:%ld b:%ld a1:%ld m:%ld result:%ld\n",a,b,a1,m,result);
  return (int64_t)result;
}

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  int a_bi[63];
  int64_t result=0;
  int len1=sizeof(a_bi)/sizeof(a_bi[0]);
  init(a,a_bi,len1);
  int64_t b_mod[63];
  int len2=sizeof(b_mod)/sizeof(b_mod[0]);
  init_b(b,m,b_mod,len2);
  print_b(b_mod,len2);
  assert(len1==len2);
  for(int i=0;i<len1;i++){
    int64_t temp=(int64_t)a_bi[i]*b_mod[i];
    result=add_mod(result,temp,m);
    printf("i:%d result:%ld\n",i,result);
  }
  return result;
}
