#include "perf.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>

void dummy() {
}

void print_hello() {
  printf("hello\n");
}

void print_error() {
  printf("invalid subject!\n");
  exit(1);
}

void simple_loop() {
  for (volatile int i = 0; i < 1000000; i++) ;
}
int64_t plus(int64_t a, int64_t b, int64_t c, int64_t d, int64_t m)
{
	int64_t ans = 0;
	a = a % m;
	b = b % m;
	c = c % m;
	d = d % m;
	if (a > 0x3fffffffffffffff)
	{
		ans = (ans + a - m) % m;
	}
	else
	{
		ans = (ans + a) % m;
	}
	if (b > 0x3fffffffffffffff)
	{
		ans = (ans + b - m) % m;
	}
	else
	{
		ans = (ans + b) % m;
	}
	if (c > 0x3fffffffffffffff)
	{
		ans = (ans + c - m) % m;
	}
	else
	{
		ans = (ans + c) % m;
	}
	if (d > 0x3fffffffffffffff)
	{
		ans = (ans + d - m) % m;
	}
	else
	{
		ans = (ans + d) % m;
	}
	return ans;
}
const int64_t limit1 = 0x7fffffffffffffff / 100;
const int64_t limit2 = 0x7fffffffffffffff / 10;

int64_t multimod_p1(int64_t a, int64_t b, int64_t m)
{
	a = a % m;
	b = b % m;
	int64_t temp = a * b;
	if (temp / a == b)
	{
		return temp % m;
	}
	else
	{
		int64_t a1 = a / 2;
		int64_t a2 = a - a1;
		int64_t b1 = b / 2;
		int64_t b2 = b - b1;
		return plus(multimod_p1(a1, b1, m), multimod_p1(a1, b2, m), multimod_p1(a2, b1, m), multimod_p1(a2, b2, m), m);
	}
	return 0;
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
_Bool mul_exeed(int64_t a,int64_t b);
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
int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int a_bi[63];
  int64_t result=0;
  a=a%m;
  b=b%m;
  if(!mul_exeed(a,b)){
    return a*b%m;
  }
  int len1=sizeof(a_bi)/sizeof(a_bi[0]);
  init(a,a_bi,len1);
  int64_t b_mod[63];
  int len2=sizeof(b_mod)/sizeof(b_mod[0]);
  init_b(b,m,b_mod,len2);
  assert(len1==len2);
  for(int i=0;i<len1;i++){
    int64_t temp=(int64_t)a_bi[i]*b_mod[i];
    result=add_mod(result,temp,m);
  }
  return result;

}

int64_t multimod_p3(int64_t a, int64_t b, int64_t m) {
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}

void p1()
{
  FILE *fp = fopen("multimod.txt", "r");
  int64_t a, b, m, ans;
  int sign;
  //count=0;
  while(!feof(fp))
  {
    fscanf(fp, "%ld %ld %ld %ld %d", &a, &b, &m, &ans, &sign);
    multimod_p1(a, b ,m);
    //count++;
  }
  fclose(fp);
  //printf("count: %ld\n",count);
}

void p2()
{
  FILE *fp = fopen("multimod.txt", "r");
  int64_t a, b, m, ans;
  int sign;
  while(!feof(fp))
  {
    fscanf(fp, "%ld %ld %ld %ld %d", &a, &b, &m, &ans, &sign);
    multimod_p2(a, b ,m);
  }
  fclose(fp);
}

void p3()
{
  FILE *fp = fopen("multimod.txt", "r");
  int64_t a, b, m, ans;
  int sign;
  while(!feof(fp))
  {
    fscanf(fp, "%ld %ld %ld %ld %d", &a, &b, &m, &ans, &sign);
    multimod_p3(a, b ,m);
  }
  fclose(fp);
}
