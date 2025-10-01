#ifndef VALUE_H
#define VALUE_H

#include "common.h"
#include "memory.h"

typedef double Value;

typedef struct ValueArray{
  int capacity;
  int count;
  Value *values;
}ValueArray;

void initValueArray(ValueArray *valueArr);
void writeValueArray(ValueArray *valueArr, Value value);
void freeValueArray(ValueArray * valueArr);
void printValue(Value value);

#endif
