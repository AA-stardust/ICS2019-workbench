#include<stdio.h>
int test(){
    int a=10, b=1;
    int c;
    asm (
    "movl %1, %%eax\n\t" 
    "addl %2, %%eax\n\t"
    "movl %%eax, %0"
    :"=r"(c)        /* output */
    :"r"(a),"r"(b)         /* input */
    :"%eax"         /* clobbered register */
    );       
    printf("b: %d\n",b);
    printf("c: %d\n",c);
    return 0;
}