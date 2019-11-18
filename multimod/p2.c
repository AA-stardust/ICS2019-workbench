#include "multimod.h"
#include<stdio.h>
void init(int64_t a,int b[],int len){
  int i=0;
  while(i<len){
    b[i]=a%2;
    a/=2;
    i++;
  }
}
void print(int a[],int len){
  for(int i=0;i<len;i++){
    printf("%d ",a[i]);
    if((i+1)%5==0)printf("\n");
  }
}
int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int a_bi[63];
  int len=sizeof(a_bi)/sizeof(a_bi[0]);
  init(a,a_bi,len);
  printf("%lx\n",a);
  print(a_bi,len);
  return -2;
}
