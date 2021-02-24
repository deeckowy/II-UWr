/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  Blocks are never coalesced or reused.  The size of
 * a block is found at the first aligned word before the block (we need
 * it for realloc).
 *
 * This code is correct and blazingly fast, but very bad usage-wise since
 * it never frees anything.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

#define list_count 16

typedef struct {
  int32_t header;
  int32_t prev;
  int32_t next_free;
  int32_t prev_free;
  /*
   * We don't know what the size of the payload will be, so we will
   * declare it as a zero-length array.  This allow us to obtain a
   * pointer to the start of the payload.
   */
  uint8_t payload[];
} block_t;

static block_t **free_list;
static void *heap_start;
static block_t *lastblock;
static int32_t listmask;

static inline size_t round_up(size_t size) {
  return (size + ALIGNMENT - 1) & -ALIGNMENT;
}

static inline size_t get_size(block_t *block) {
  return block->header & -2;
}

static inline void set_header(block_t *block, size_t size, bool is_allocated) {
  block->header = size | is_allocated;
}

static inline int32_t shrink_addr(void *adrr)
{
  return adrr-heap_start;
}

static inline block_t *next_block(block_t *block)
{
  return (void*)block+(block->header&-2);
}

static inline bool is_free(block_t *block)
{
  return !(block->header&1);
}

static inline void *prev_block(block_t *block)
{
  return heap_start+block->prev;
}

static inline void *next_free_block(block_t *block)
{
  return heap_start+block->next_free;
}

static inline void *prev_free_block(block_t *block)
{
  return heap_start+block->prev_free;
}

static inline void set_prev(block_t *block,int32_t off)
{
  block->prev=off;
}

static inline void set_next_free(block_t *block,int32_t off)
{
  block->next_free=off;
}

static inline void set_prev_free(block_t *block,int32_t off)
{
  block->prev_free=off;
}

static inline void set_free(block_t *block)
{
  block->header&=-2;
}

static int list_index(size_t size)
{
  int idx=-5;
  while((size>>=1))idx++;
  return idx>listmask?listmask:idx;
}

static void insert_to_list(block_t *block,int idx)
{
  if(free_list[idx])
  {
    set_next_free(block,shrink_addr(free_list[idx]));
    set_prev_free(free_list[idx],shrink_addr(block));
    set_prev_free(block,-1);
    free_list[idx]=block;
  }
  else 
  {
    free_list[idx]=block;
    set_next_free(block,-1);
    set_prev_free(block,-1);
  }
}

static block_t *lookup(size_t size,int idx)
{
  block_t *block=free_list[idx];
  if(block)
  {
    while((void*)block>=heap_start)
    {
      if(get_size(block)>=size)
        return block;
      else 
        block=next_free_block(block);
    }
  }
  return NULL;
}


static block_t *find_free(size_t size)
{
  block_t *output=NULL;
  for(int i=list_index(size);i<list_count;i++)
  {
    output=lookup(size,i);
    if(output)
      return output;
  }
  return output;
}

static void remove_from_list(block_t *block,int idx)
{
  block_t *pblock=prev_free_block(block);
  block_t *nblock=next_free_block(block);
  if((void*)pblock<heap_start&&(void*)nblock<heap_start)
    free_list[idx]=NULL;
  else 
  {
    if((void*)nblock>=heap_start)
      set_prev_free(nblock,block->prev_free);
    if(block==free_list[idx])
      free_list[idx]=nblock;
    else 
      set_next_free(pblock,block->next_free);
  }
}


static void merge(block_t *block,block_t *nblock)
{
  if(nblock==lastblock)
    lastblock=block;
  else 
  {
    block_t *nnblock=next_block(nblock);
    set_prev(nnblock,shrink_addr(block));
  }
  size_t ssize=get_size(block)+get_size(nblock);
  set_header(block,ssize,false);
}

static void split(block_t *block,size_t size)
{
  size_t bsize=get_size(block);
  if(bsize<=size+16)
    return;
  block_t *nblock=next_block(block);
  size_t nsize=bsize-size;
  set_header(block,size,false);
  block_t *sblock=next_block(block);
  set_header(sblock,nsize,false);
  int idx=list_index(nsize);
  insert_to_list(sblock,idx);
  set_prev(sblock,shrink_addr(block));
  if(block!=lastblock)
    set_prev(nblock,shrink_addr(sblock));
  else 
    lastblock=sblock;
}
/*
 * mm_init - Called when a new trace starts.
 */
int mm_init(void) {
  /* Pad heap start so first payload is at ALIGNMENT. */
  if ((long)mem_sbrk(ALIGNMENT - offsetof(block_t, payload)) < 0)
    return -1;
  free_list=mem_sbrk(sizeof(block_t*)*list_count);
  heap_start=mem_heap_hi()+1;
  lastblock=heap_start-1;
  for(int i=0;i<list_count;i++)
  {
    free_list[i]=NULL;
  }
  listmask=list_count-1;
  return 0;
}

static inline void set_nonfree(block_t *block)
{
  block->header|=1;
}

/*
 * malloc - Allocate a block by incrementing the brk pointer.
 *      Always allocate a block whose size is a multiple of the alignment.
 */
void *malloc(size_t size) {
  size = round_up(sizeof(block_t) + size);
  block_t *block = NULL;
  if((block=find_free(size)))
  {
    size_t siz=get_size(block);
    int idx=list_index(siz);
    remove_from_list(block,idx);
    split(block,size);
    set_nonfree(block);
    return block->payload;
  }
  else 
  {
    block = mem_sbrk(size);
    if ((long)block < 0)
      return NULL;
    set_header(block, size, true);
    set_prev(block,shrink_addr(lastblock));
    set_prev_free(block,-1);
    set_next_free(block,-1);
    lastblock=block;
    return block->payload;
  }
}

/*
 * free - We don't know how to free a block.  So we ignore this call.
 *      Computers have big memories; surely it won't be a problem.
 */
void free(void *ptr) {
  block_t *block = ptr - offsetof(block_t, payload);
  set_free(block);
  if(block!=lastblock)
  {
    block_t *nblock=next_block(block);
    if(is_free(nblock))
    {
      int idx=list_index(get_size(nblock));
      remove_from_list(nblock,idx);
      merge(block,nblock);
    }
  }
  if(block!=heap_start)
  {
    block_t *pblock=prev_block(block);
    if(is_free(pblock))
    {
      int idx=list_index(get_size(pblock));
      remove_from_list(pblock,idx);
      merge(pblock,block);
      block=pblock;
    }
  }
  size_t size=get_size(block);
  int idx=list_index(size);
  insert_to_list(block,idx);
}

/*
 * realloc - Change the size of the block by mallocing a new block,
 *      copying its data, and freeing the old block.
 **/
void *realloc(void *old_ptr, size_t size) {
  /* If size == 0 then this is just free, and we return NULL. */
  if (size == 0) {
    free(old_ptr);
    return NULL;
  }
  size=round_up(size+sizeof(block_t));
  /* If old_ptr is NULL, then this is just malloc. */
  if (!old_ptr)
    return malloc(size);

  block_t *block = old_ptr - offsetof(block_t, payload);
  size_t old_size = get_size(block);
  //we need less size => split block and mark new block as free
  if(size<=old_size)
  {
    split(block,size);
    set_nonfree(block);
    return block->payload;
  }
  //if next block is free and have enough size just merge them
  block_t *nblock=next_block(block);
  if(block!=lastblock)
    old_size+=is_free(nblock)*get_size(nblock);
  else 
  {
    //last block on heap so we can just make heap bigger 
    size_t nsize=size-old_size;
    mem_sbrk(nsize);
    set_header(block,size,true);
    return block->payload;
  }
  //check if merging will do
  if(old_size>=size)
  {
    size_t nsize=get_size(nblock);
    int idx=list_index(nsize);
    remove_from_list(nblock,idx);
    merge(block,nblock);
    split(block,size);
    set_nonfree(block);
    return block->payload;
  }
  else 
  {
    //worst case => we have to alloc a new block and copy data
    void *new_ptr=malloc(size);
    if(!new_ptr)return NULL;
    memcpy(new_ptr,old_ptr,old_size);
    free(old_ptr);
    return new_ptr;
  }
  return NULL;
}

/*
 * calloc - Allocate the block and set it to zero.
 */
void *calloc(size_t nmemb, size_t size) {
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);

  /* If malloc() fails, skip zeroing out the memory. */
  if (new_ptr)
    memset(new_ptr, 0, bytes);

  return new_ptr;
}

/*
 * mm_checkheap - So simple, it doesn't need a checker!
 */
void mm_checkheap(int verbose) {
}

