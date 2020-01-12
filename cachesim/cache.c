#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);
static uint64_t hit_number=0;
static uint64_t cycle_cnt = 0;

void cycle_increase(int n) { cycle_cnt += n; }
typedef struct{
  bool dirty_bit:1;
  bool valid_bit:1;
  uint32_t tag:13;
  uint8_t data[64];
}cache_line;

cache_line *Cache;
// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  uint32_t ret_data=0;
  uint32_t paddr;
  cycle_increase(1);
  addr&=0x1ffffff;
  uint32_t block_offset=addr&0x3C;
  uint32_t group_number=(addr>>6)&0x3F;
  uint32_t tag=(addr>>12)&0x1FFF;
  uint32_t blocks_number=(addr>>6)&0x7FFFF;
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
        break;
      }
    }
    if(j<start+4){
      mem_read(blocks_number,Cache[j].data);
      Cache[j].tag=tag;
      Cache[j].valid_bit=1;
      ret_data=Cache[j].data[block_offset]+(Cache[j].data[block_offset+1]<<8)+(Cache[j].data[block_offset+2]<<16)+(Cache[j].data[block_offset+3]<<24);
    }
    else{
      flag=rand()%4+start;
      if(Cache[flag].dirty_bit==1){
        paddr=(Cache[flag].tag<<6)|group_number;
        mem_write(paddr,Cache[flag].data);
      }
      mem_read(blocks_number,Cache[flag].data);
      Cache[flag].tag=tag;
      Cache[flag].valid_bit=1;
      ret_data=Cache[flag].data[block_offset]+(Cache[flag].data[block_offset+1]<<8)+(Cache[flag].data[block_offset+2]<<16)+(Cache[flag].data[block_offset+3]<<24);
    }
  }
  return ret_data;
}
void renew(int i,uint32_t block_offset,uint32_t wmask,uint32_t data){
  uint32_t new_data;
  uint32_t old_data=Cache[i].data[block_offset]+(Cache[i].data[block_offset+1]<<8)+(Cache[i].data[block_offset+2]<<16)+(Cache[i].data[block_offset+3]<<24);
  new_data=(old_data&(~wmask))|(data&wmask);
  Cache[i].data[block_offset+3]=(new_data>>24)&0xFF;
  Cache[i].data[block_offset+2]=(new_data>>16)&0xFF;
  Cache[i].data[block_offset+1]=(new_data>>8)&0xFF;
  Cache[i].data[block_offset]=new_data&0xFF;
}
void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  uint32_t paddr;
  addr=addr&0x1ffffff;
  uint32_t block_offset=addr&0x3C;
  uint32_t group_number=(addr>>6)&0x3F;
  uint32_t tag=(addr>>12)&0x1FFF;
  uint32_t blocks_number=(addr>>6)&0x7FFFF;
  cycle_increase(1);
  uint32_t start=group_number+4;
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
    renew(i,block_offset,wmask,data);
    Cache[i].dirty_bit=1;
  }
  else{
    for(j=start;j<start+4;j++){
      if(Cache[j].valid_bit==0)break;
    }
    if(j<start+4){
      mem_read(blocks_number,Cache[j].data);
      renew(j,block_offset,wmask,data);
      Cache[j].tag=tag;
      Cache[j].valid_bit=1;
      Cache[j].dirty_bit=1;
    }
    else{
      flag=rand()%4+start;
      if(Cache[flag].dirty_bit==1){
        paddr=(Cache[flag].tag<<6)|group_number;
        mem_write(paddr,Cache[flag].data);
      }
      mem_read(blocks_number,Cache[flag].data);
      renew(flag,block_offset,wmask,data);
      Cache[flag].tag=tag;
      Cache[flag].valid_bit=1;
      Cache[flag].dirty_bit=1;
    }
  }
}

void init_cache(int total_size_width, int associativity_width) {
  int i;
  int line=exp2(total_size_width-6);
  Cache=malloc(line*sizeof(cache_line));
  for(i=0;i<line;i++){
    Cache[i].valid_bit=0;
    Cache[i].dirty_bit=0;
  }
}
extern uint32_t wrong_time;
void display_statistic(void) {
  printf("cycle time: %ld\n",cycle_cnt);
  printf("hit: %ld\n",hit_number);
  double hit_partial=(double)hit_number/cycle_cnt;
  printf("hit rate: %lf\n",hit_partial);
  printf("wrong_time: %u\n",wrong_time/2);
}
