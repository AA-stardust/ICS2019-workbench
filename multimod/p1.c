#include "multimod.h"
#include<stdio.h>
_Bool mul_exeed(int64_t a,int64_t b){
  int64_t c=a*b;
  printf("exeed: c=%ld\n",c);
  printf("exeed: a=%ld\n",a);
  printf("exeed: c/b=%ld\n",c/b)
  return !(b==0||a==c/b);
}
int64_t add_mod(int64_t a,int64_t b,int64_t m){
  uint64_t a1=a+b;
  uint64_t result=a1%(uint64_t)m;
  return (int64_t)result;
}

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  int64_t a1=a>b? a:b;
  int64_t b1=a<b? a:b;
  a1=a1%m;
  b1=b1%m;
  if(!mul_exeed(a1,b1)){
    printf("process 1\n");
    return (a1*b1)%m;
  }
  int64_t result=0;
  for(int i=0;i<b1;i++){
    result=add_mod(result,a1,m);
  }
  printf("process 2\n");
  return result;
}
