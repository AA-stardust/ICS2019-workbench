#include<stdio.h>
#include<setjmp.h>
jmp_buf buf;
int test(){
    /*int a=10, b=1;
    int c;
    asm (
    "movl %1, %%eax\n\t" 
    "addl %2, %%eax\n\t"
    "movl %%eax, %0"
    :"=r"(c)        
    :"r"(a),"r"(b)        
    :"%eax"         
    );       
    printf("b: %d\n",b);
    printf("c: %d\n",c);
    return 0;*/
    if(!setjmp(buf)){
        printf("0\n");
        longjmp(buf,1);
    }
    printf("out\n");
    return 0;
}