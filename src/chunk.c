#include "chunk.h"

void initChunk(Chunk *chunk){
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = 0;
  chunk->lines = NULL;
  chunk->lineCount = 0;
  chunk->lineCapacity = 0;
  initValueArray(&chunk->constants);
}

void initLinesArray(int *lines, int startIndex, int endIndex){
  for(int i = startIndex; i < endIndex; i++){
    lines[i] = 0;
  }
}

void freeChunk(Chunk *chunk){
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line){

  if(chunk->capacity < chunk->count + 1){
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;
  if(chunk->lineCount > 0){
    for(int i = 0; i < chunk->lineCount; i++){
      if(chunk->lines[i] == line && i % 2 == 0){
        chunk->lines[i + 1]++;
        return;
      }
    }
  }
  else if(chunk->lineCount + 2 > chunk->lineCapacity){
    int oldCapacity = chunk->lineCapacity;
    chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->lineCapacity);
    initLinesArray(chunk->lines, oldCapacity, chunk->capacity);
  }
  chunk->lines[chunk->lineCount++] = line;
  chunk->lines[chunk->lineCount++] = 1;
}

int addConstant(Chunk *chunk, Value value){
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1; //return the index
}
