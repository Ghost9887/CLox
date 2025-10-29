#include "debug.h"
#include <stdio.h>

static int simpleInstruction(const char *name, int offset){
  printf("%s\n", name);
  //this instruction only has a size of one so return the next index
  return offset + 1;
}

int dissasembleInstruction(Chunk *chunk, int offset){
  printf("%04d ", offset); //print the offset(index)

  uint8_t instruction = chunk->code[offset];
  switch(instruction){
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Uknown opcode %d\n", instruction);
      return offset + 1;
  }
}

void dissasembleChunk(Chunk *chunk, const char *name){
  printf("== %s ==\n", name);

  //we loop through the code array with the offset(index)
  //the offset gets incremented depending on the instruction(code[index])
  //we dissasemble as each one has a different size(index + size)
  for(int offset = 0; offset < chunk->count;){
    offset = dissasembleInstruction(chunk, offset);
  }
}
