#include "multimod.h"
#include<stdio.h>
#include<assert.h>
extern int64_t add_mod(int64_t a,int64_t b,int64_t m);
void init(int64_t a,int b[],int len){
  int i=0;
  while(i<len){
    b[i]=a%2;
    a/=2;
    i++;
  }
}
void init_b(int64_t b,int64_t m,int64_t b_m[],int len){
  int i=0;
  int64_t result=b;
  while(i<len){
    if(i==0){
      b_m[i]=result%m;
      result%=m;
      i++;
      continue;
    }
    result=add_mod(result,result,m);
    b_m[i]=result;
    i++;
  }
}
void print(int a[],int len){
  for(int i=0;i<len;i++){
    printf("%d ",a[i]);
    if((i+1)%5==0)printf("\n");
  }
}
void print_b(int64_t b[],int len){
  for(int i=0;i<len;i++){
    printf("%ld ",b[i]);
    if((i+1)%5==0)printf("\n");
  }
}
int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
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
