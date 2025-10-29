#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[]){
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);

  //returns the index
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);

  int constant1 = addConstant(&chunk, 3.0);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant1);

  dissasembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
