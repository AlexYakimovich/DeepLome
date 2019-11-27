typedef enum smMemoryType
{
  SM_MEMORY_READ_ONLY,
  SM_MEMORY_WRITE_ONLY,
  SM_MEMORY_FULL_ACCESS
} SmMemoryType;

typedef struct {
  unsigned int Id;
  unsigned int Size;
  void * Data;
  SmMemoryType Type;
} SmMemoryEntity;

typedef SmMemoryEntity* SmMemory;

int InitializeSmMemory(SmMemory * memory, unsigned int size, SmMemoryType type);

int ReleaseSmMemory(SmMemory memory);