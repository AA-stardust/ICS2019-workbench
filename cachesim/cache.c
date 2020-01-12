#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);
static uint64_t hit_number=0;
static uint64_t cycle=0;
static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }
typedef struct{
  bool dirty_bit:1;
  bool valid_bit:1;
  uint32_t tag:13;
  uint8_t data[64];
}cache_line;

cache_line*Cache;
// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  uint32_t ret_data=0;
  uint32_t pa;
  cycle_increase(1);
  addr&=0x1ffffff;
  uint32_t block_offset=addr&0x3c;
  uint32_t group_number=(addr>>6)&0x3f;
  uint32_t tag=(addr>>12)&0x1fff;
  uint32_t blocks_number=(addr>>6)&0x7ffff;
  uint32_t start=group_number*4;
  int i=0;
  int j=0;
  int flag;
  for(i=start;i<start+4;i++){
    if(Cache[i].tag==tag&&Cache[i].valid_bit==1){
      hit_number++;
      break;
    }
  }
  if(i<start+4){
    ret_data=Cache[i].data[block_offset]+(Cache[i].data[block_offset+1]<<8)+(Cache[i].data[block_offset+2]<<16)+(Cache[i].data[block_offset+3]<<24);

  }
  else{
    for(j=start;j<start+4;j++){
      if(Cache[j].valid_bit==0){

      }
    }
  }
  return ret_data;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
}

void init_cache(int total_size_width, int associativity_width) {
}

void display_statistic(void) {
}
