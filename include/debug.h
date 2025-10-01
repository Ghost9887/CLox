#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);

#endif
