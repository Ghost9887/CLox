#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"

void dissasembleChunk(Chunk *chunk, const char *name);
int dissasembleInstruction(Chunk *chunk, int offset);

#endif
