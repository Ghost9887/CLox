#ifndef COMPILER_H
#define COMPILER_H

#include "common.h"
#include "scanner.h"
#include "chunk.h"

bool compile(const char *source, Chunk *chunk);

#endif
