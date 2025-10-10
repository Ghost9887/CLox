#ifndef MEMORY_H
#define MEMORY_H

#include "common.h"

//macro to grow capacity
#define GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (capacity) * 2)

//macro to grow array
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
  (type*)reallocate(pointer, sizeof(type) * (oldCount), \
      sizeof(type) * (newCount))

//macro to free array
#define FREE_ARRAY(type, pointer, oldCount) \
  reallocate(pointer, sizeof(type) * oldCount, 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
