#include "sm_connection.h"
#include <stdlib.h>

int InitializeSmConnection(SmConnection * connection, Socket sock)
{
  SmConnection conn = malloc(sizeof(SmConnectionEntity));
  conn->Memory = malloc(sizeof(SmMemory) * MAX_MEMORY_SIZE);
  conn->MemorySize = 0;
  conn->Socket = sock;
  *connection = conn;
  return 0;
}

int SmConnectionGetData(SmConnection connection)
{
  for (int i = 0; i < connection->MemorySize; i++)
  {
    const SmMemory mem = connection->Memory[i];
    if (mem->Type == SM_MEMORY_WRITE_ONLY)
      continue;
    if (mem->Size != SocketRecv(connection->Socket, mem->Data, mem->Size))
      return -1;
  }
  return 0;
}

int SmConnectionSetData(SmConnection connection)
{
  for (int i = 0; i < connection->MemorySize; i++)
  {
    const SmMemory mem = connection->Memory[i];
    if (mem->Type == SM_MEMORY_READ_ONLY)
      continue;
    if (mem->Size != SocketSend(connection->Socket, mem->Data, mem->Size))
      return -1;
  }
  return 0;
}

int AttachSmMemoryToSmConnection(SmConnection connection, SmMemory mem)
{
  connection->Memory[connection->MemorySize] = mem;
  connection->MemorySize++;
  return 0;
}

int ReleaseSmConnection(SmConnection connection)
{
  free(connection->Memory);
  free(connection);
  return 0;
}
