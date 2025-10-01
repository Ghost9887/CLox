#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "memory.h"
#include "value.h"

typedef enum OpCode{
  OP_CONSTANT,
  OP_RETURN
}OpCode;

//dynamic array
typedef struct Chunk{
  int count;
  int capacity;
  uint8_t *code;
  int *lines;
  int lineCount;
  int lineCapacity;
  ValueArray constants;
}Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);

#endif
