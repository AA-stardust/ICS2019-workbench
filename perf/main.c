#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include<unistd.h>
#include<sys/time.h>
#define DECL(fn) void fn();

PROGRAMS(DECL)

static void run(void (*func)(), int rounds);
static uint64_t gettime();
static void (*lookup(const char *fn))();
extern char* optarg;
extern int optind;
char func_name[30];
int main(int argc, char **argv) {
  // TODO: parse arguments: set @func and @rounds
  //void (*func)() = lookup("dummy");
  int rounds = 1;
  int res=0;
  while(((res=getopt(argc,argv,"r:"))!=-1)){
    switch(res){
      case 'r':
        if(optarg==NULL){
          printf("Please input rounds\n");
          assert(0);
        }
        rounds=atoi(optarg);
        if(rounds<=0){
          printf("rounds have to be positive\n");
          assert(0);
        }
        break;
      case 1:{
        printf("%s\n",argv[optind]);
        break;
      }
      default:
        printf("res: %d\n",res);
        printf("invalid input\n");
        assert(0);
    }
  }
  printf("rounds:%d\n",rounds);
  void (*func)()=lookup(argv[argc-1]);
  strcpy(func_name,argv[argc-1]);
  run(func, rounds);
}

static uint64_t gettime() {
  // TODO: implement me!
  struct timeval time_s;
  gettimeofday(&time_s,NULL);
  double cur_time=(double)time_s.tv_sec+(double)time_s.tv_usec/1000000;
  return cur_time;
  return time(NULL);
}

static void (*lookup(const char *fn))() {
  #define PAIR(fn) { #fn, fn },
  struct pair {
    const char *name;
    void *ptr;
  };
  struct pair lut[] = {
    PROGRAMS(PAIR)
  };

  for (int i = 0; i < LENGTH(lut); i++) {
    struct pair *p = &lut[i];
    if (strcmp(fn, p->name) == 0) return p->ptr;
  }
  return print_error;
}

static void run(void (*func)(), int rounds) {
  double *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  for (int round = 0; round < rounds; round++) {
    double st = gettime();
    func();
    double ed = gettime();
    elapsed[round] = ed - st;
  }
  double mark_ave=0;
  double mark_min=elapsed[0];
  double mark_max=elapsed[0];
  for(int round=0;round<rounds;round++){
    mark_ave+=elapsed[round];
    if(elapsed[round]<mark_min)mark_min=elapsed[round];
    if(elapsed[round]>mark_max)mark_max=elapsed[round];
  }
  mark_ave/=rounds;
  printf("Average time of %s is %lf\n",func_name,mark_ave);
  printf("Minimum time of %s is %lf\n",func_name,mark_min);
  printf("Maximun time of %s is %lf\n",func_name,mark_max);
  // TODO: display runtime statistics
  double var=0;
  for(int round=0;round<rounds;round++){
    var+=(elapsed[round]-mark_ave)*(elapsed[round]-mark_ave);
  }
  var/=rounds;
  printf("Variance of %s is %lf\n",func_name,var);
  free(elapsed);
}
