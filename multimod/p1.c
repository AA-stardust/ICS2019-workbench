#include "multimod.h"
#include<stdio.h>
_Bool exeed(int64_t a,int64_t b){
  int64_t c=a*b;
  return !(b==0||a==c/b);
}

int64_t multimod_square(int64_t a,int64_t m){
  if(a==0)return 0;
  if(m==0)return -1;
  int64_t a1;
  int64_t m1;
  if(a>m){
	a1=a;
	m1=m;
  }
  if(a==m)return 0;
  if(a<m){
	a1=m;
	m1=a;
  }
  int64_t x=a1/m1;
  int64_t i=x;
  for(i=x;a1-i*m1>0;i++){
	if(!exeed(a1-i*m1,a1-i*m1)){
		int64_t c=(a1-i*m1)*(a1-i*m1);
		return c%m;
	}
  }
  return -1;
}
void swap(int64_t *a,int64_t *b){
	int64_t temp=*a;
	*a=*b;
	*b=temp;
}
int64_t add_mod(int64_t a,int64_t b){
  
}

int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
 /* int i=1;
  int result=0;
  for(int i=1;i<=b;i++){
	result+=a%m;
	result%=m;
  }
  //uint64_t c=a*b;
  //result=c%m;*/
  if(m==0)return -1;
  if(m==1)return 0;
  if(m==2){
	if(a%2==0||b%2==0)return 0;
	return 1;
  }
  if(a==m||b==m)return 0;
 /* int64_t a1=a>m? a:m;
  int64_t m1=a>m? m:a;
  int64_t b1=b>m? b:m;
  int64_t m2=b>m? m:b;
  int64_t i;
  i=a1/m1;
  int64_t c1=a1-i*m1;
  c1%=m;
  i=a2/m2;
  int64_t c2=a2-i*m2;
  c2%=m2;
  int64_t c=c1*c2%m;*/
  if(a<b)swap(&a,&b);
  if(b==0)return 0;
  if(a==b)return multimod_square(a,m);
  int64_t div[4];
  div[1]=multimod_square(a,m);
  div[2]=multimod_square(b,m);
  div[3]=multimod_square(a-b,m);
  div[0]=(div[1]+div[2]-div[3])%m;//div[0]保存2*a*b%m的值
  if(div[0]%2==0)return div[0]/2;
  if(div[0]%2!=0)return div[0]/2+m/2+1;
  /*if(result>=0)
	return result;
  return -1;*/
}
