#include "socket.h"
#include "sm_memory.h"
#define MAX_MEMORY_SIZE 100

typedef struct {
  Socket Socket;
  SmMemory * Memory;
  unsigned int MemorySize;
} SmConnectionEntity;

typedef SmConnectionEntity* SmConnection;

int InitializeSmConnection(SmConnection * connection, Socket sock);

int SmConnectionGetData(SmConnection connection);

int SmConnectionSetData(SmConnection connection);

int AttachSmMemoryToSmConnection(SmConnection connection, SmMemory mem);

int ReleaseSmConnection(SmConnection connection);