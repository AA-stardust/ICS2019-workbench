#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include<unistd.h>
#define DECL(fn) void fn();

PROGRAMS(DECL)

static void run(void (*func)(), int rounds);
static uint64_t gettime();
static void (*lookup(const char *fn))();
extern char* optarg;
extern int optind;
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
  run(func, rounds);
}

static uint64_t gettime() {
  // TODO: implement me!
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
  uint64_t *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  for (int round = 0; round < rounds; round++) {
    uint64_t st = gettime();
    func();
    uint64_t ed = gettime();
    elapsed[round] = ed - st;
  }

  // TODO: display runtime statistics

  free(elapsed);
}
