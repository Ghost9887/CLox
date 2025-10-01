#include "debug.h"

static int simpleInstruction(const char *name, int offset){
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset){
  uint8_t constant = chunk->code[offset + 1]; //stores the value after the constant declaration
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]); //uses the index of teh constant
  printf("'\n");
  return offset + 2; //uses two slots in the code array
}

static int constantLongInstruction(const char *name, Chunk *chunk, int offset){
  uint32_t constant = chunk->code[offset + 1] |
                     (chunk->code[offset + 2] << 8) |
                     (chunk->code[offset + 3] << 16);
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 4;
}

int getLine(Chunk *chunk, int instructionIndex) {
  int offset = 0;
  for (int i = 0; i < chunk->lineCount; i += 2) {
    int line = chunk->lines[i];
    int count = chunk->lines[i + 1];
    if (instructionIndex < offset + count) {
      return line;
    }
    offset += count;
  }
  return -1;
}


int disassembleInstruction(Chunk *chunk, int offset){
  printf("%04d ", offset);

  //show the line where a error happened
  int line = getLine(chunk, offset);
  if(offset > 0 && line == getLine(chunk, offset - 1)){
    printf("  | ");
  }else{
    printf("%4d ", line);
  }

  uint8_t instruction = chunk->code[offset];
  switch(instruction){
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_CONSTANT_LONG:
      return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
    default:
      printf("Uknown opcode %d\n", instruction);
      return offset + 1;
  }
}

void disassembleChunk(Chunk *chunk, const char *name){
  printf("== %s ==\n", name);
  for(int offset = 0; offset < chunk->count;){ //offset == chunk->code[offset];
    offset = disassembleInstruction(chunk, offset);
  }
}

