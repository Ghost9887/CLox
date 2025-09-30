#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

typedef enum OpCode{
  OP_RETURN
}OpCode;

//dynamic array
typedef struct Chunk{
  int count;
  int capacity;
  uint8_t *code;
}Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t *byte);

#endif
