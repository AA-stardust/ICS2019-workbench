#include"p3.c"
#include<stdio.h>
int main(){
    FILE *fp=fopen("python.txt","r");
    int64_t a;
    int64_t b;
    int64_t m;
    int64_t result;
    int64_t result2;
    int error=0;
    while(!feof(fp)){
        fscanf(fp,"%ld %ld %ld %ld\n",&a,&b,&m,&result);
        result2=multimod_p3(a,b,m);
        if(result2!=result){
            error++;
            printf("%ld %ld %ld true: %ld error: %ld\n",a,b,m,result,result2);
        }
    }
    printf("total: 1000 error: %d\n",error);
    fclose(fp);
    return 0;
}