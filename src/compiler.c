#include "compiler.h"

//TODO: implement parse precedence

void expression();

typedef struct{
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
}Parser;

Parser parser;

typedef enum{
  PREC_NONE,
  PREC_ASSIGNMENT, // =
  PREC_OR, // or
  PREC_AND, // and
  PREC_EQUALITY, // == !=
  PREC_COMPARISON, // < > <= >=
  PREC_TERM, // + -
  PREC_FACTOR, // * /
  PREC_UNARY, // ! -
  PREC_CALL, // . ()
  PREC_PRIMARY
}Precedence;

Chunk *compilingChunk;

Chunk *currentChunk(){
  return compilingChunk;
}

void errorAt(Token *token, const char *message){
  if(parser.panicMode) return; //skip any errors if we already have one
  parser.panicMode = true;
  fprintf(stderr, "[line %d] Error", token->line);
  if(token->type == TOKEN_EOF){
    fprintf(stderr, " at end");
  }
  else if(token->type == TOKEN_ERROR){
    //Nothing
  }
  else {
    fprintf(stderr, " at '%.s'", token->length, token->start);
  }
  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

void error(const char *message){
  errorAt(&parser.previous, message);
}

void errorAtCurrent(const char *message){
  errorAt(&parser.current, message);
}

void advance(){
  parser.previous = parser.current;
  for(;;){
    parser.current = scanToken();
    if(parser.current.type != TOKEN_ERROR) break;
    errorAtCurrent(parser.current.start);
  }
}

void consume(TokenType type, const char *message){
  if(parser.current.type == type){
    advance();
    return;
  }
  errorAtCurrent(message);
}

void emitByte(uint8_t byte){
  writeChunk(currentChunk(), byte, parser.previous.line);
}

void emitBytes(uint8_t byte1, uint8_t byte2){
  emitByte(byte1);
  emitByte(byte2);
}

void emitReturn(){
  emitByte(OP_RETURN);
}

uint8_t makeConstant(Value value){
  int constant = addConstant(currentChunk(), value);
  if(constant > UINT8_MAX){
    error("Too many constants in one chunk");
    return 0;
  }
  return (uint8_t)constant;
}

void emitConstant(Value value){
  emitBytes(OP_CONSTANT, makeConstant(value));
}

void endCompiler(){
  emitReturn();
}

void grouping(){
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression");
}

void number(){
  double value = strtod(parser.previous.start, NULL);
  emitConstant(value);
}

void unary(){
  TokenType operatorType = parser.previous.type;
  //compile the operand
  parsePresedence(PREC_UNARY);
  //emit the operator instruction
  switch(operatorType){
    case TOKEN_MINUS: emitByte(OP_NEGATE); break;
    default: return;
  }
}

void expression(){
  parsePresedence(PREC_ASSIGNMENT);
}

bool compile(const char *source, Chunk *chunk){
  initScanner(source);
  compilingChunk = chunk;
  parser.hadError = false;
  parser.panicMode = false;
  advance();
  expression();
  consume(TOKEN_EOF, "expected end of expression");
  endCompiler();
  return !parser.hadError;
}
