#include "chunk.h"
#include "memory.h"
#include <stdlib.h>

void initChunk(Chunk *chunk){
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
}

void writeChunk(Chunk *chunk, uint8_t byte){

  //we check if we can fit another byte into our array
  if(chunk->capacity < chunk->count + 1){
    int oldCapacity = chunk->capacity;

    //we increase the capacity
    chunk->capacity = GROW_CAPACITY(oldCapacity);

    //we grow the dynamic array
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

void freeChunk(Chunk *chunk){
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  initChunk(chunk);
}
