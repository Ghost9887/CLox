#include "memory.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize){

  //we pass in 0 to new size if we want to free the memory
  if(newSize == 0){
    free(pointer);
    return NULL;
  }
  
  void *result = realloc(pointer, newSize);
  //check if realloc has failed if so we exit the program
  if(result == NULL) exit(1);
  return result;
}

