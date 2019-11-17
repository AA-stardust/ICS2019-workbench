#include"p1.c"
#include<stdio.h>
int main(){
  int64_t a,b,m;
  FILE *fp=fopen("input","r");
  fscanf(fp,"%ld %ld %ld",&a,&b,&m);
//  scanf("%ld%ld%ld",&a,&b,&m);
  printf("(%ld*%ld)%%%ld=%ld\n",a,b,m,multimod_p1(a,b,m));
  return 0;
}
