#include "memory.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize){
  if(newSize == 0){
    //free the memory
    free(pointer);
    return NULL;
  }
  void *result = realloc(pointer, newSize);
  if(result == NULL) exit(1); //check if the realloc is successfull
  return result;
}
