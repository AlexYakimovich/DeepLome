#include "../sm_memory.h"
#include <stdlib.h>

int InitializeSmMemory(SmMemory * memory, unsigned int size, SmMemoryType type)
{
  *memory = malloc(sizeof(SmMemoryEntity));
  (*memory)->Data = malloc(size);
  (*memory)->Size = size;
  (*memory)->Type = type;
  return 0;
}

int ReleaseSmMemory(SmMemory memory)
{
  free(memory->Data);
  free(memory);
  return 0;
}
