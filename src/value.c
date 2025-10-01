#include "value.h"

void initValueArray(ValueArray *valueArr){
  valueArr->capacity = 0;
  valueArr->count = 0;
  valueArr->values = NULL;
}

void writeValueArray(ValueArray *valueArr, Value value){
  if(valueArr->capacity < valueArr->count + 1){
    int oldCapacity = valueArr->capacity;
    valueArr->capacity = GROW_CAPACITY(oldCapacity);
    valueArr->values = GROW_ARRAY(Value, valueArr->values, oldCapacity, valueArr->capacity);
  }
  valueArr->values[valueArr->count] = value;
  valueArr->count++;
}

void freeValueArray(ValueArray *valueArr){
  FREE_ARRAY(Value, valueArr->values, valueArr->capacity);
  initValueArray(valueArr);
}

void printValue(Value value){
  printf("%g", value);
}

