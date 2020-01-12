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

int64_t multimod_p2(int64_t a, int64_t b, int64_t m)
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
		int64_t a1 = a / 10;
                int64_t a2 = a % 10;
                int64_t b1 = b / 10;
                int64_t b2 = b % 10;
                int64_t ans1 = multimod_p2(a1, b1, m);
                int64_t ans2 = multimod_p2(a1, b2, m);
                int64_t ans3 = multimod_p2(a2, b1, m);
                int64_t ans4 = multimod_p2(a2, b2, m);
                if (ans1 > limit1)
                {
                        ans1 = multimod_p2(100, ans1, m);
                }
                if (ans2 > limit2)
                {
                        ans1 = multimod_p2(10, ans2, m);
                }
                if (ans3 > limit2)
                {
                        ans1 = multimod_p2(10, ans3, m);
                }
		return plus(100 * ans1, 10 *ans2, 10 * ans3, ans4, m);
	}
	return 0;
}

int64_t multimod_p3(int64_t a, int64_t b, int64_t m) {
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}

void p1()
{
  FILE *fp = fopen("multimod.txt", "r");
  int64_t a, b, m, ans,count;
  int sign;
  count=0;
  while(!feof(fp))
  {
    fscanf(fp, "%ld %ld %ld %ld %d", &a, &b, &m, &ans, &sign);
    multimod_p1(a, b ,m);
    count++;
  }
  printf("count: %d\n",count);
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
}
