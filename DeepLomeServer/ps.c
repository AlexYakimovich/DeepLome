#include "ps.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma warning(disable : 4996)

int ProxyServerInitialize(ProxyServer * p_server)
{
  ProxyServer server = malloc(sizeof(ProxyServerEntity));
  
  Socket MasterSocket = SocketCreate();
  SocketBind(MasterSocket, 1337, INADDR_ANY);
  Socket ClientSocket = SocketAccept(MasterSocket);

  InitializeSmConnection(&server->connection, ClientSocket);
  InitializeSmMemory(&server->input, 40, SM_MEMORY_READ_ONLY);
  InitializeSmMemory(&server->output, 40, SM_MEMORY_WRITE_ONLY);

  AttachSmMemoryToSmConnection(server->connection, server->input);
  AttachSmMemoryToSmConnection(server->connection, server->output);

  *p_server = server;
  return 0;
}

int ProxyServerOnBegin(ProxyServer server)
{
  return SmConnectionGetData(server->connection);
}

int ProxyServerOnCompute(ProxyServer server)
{
  memcpy(server->output->Data, "EDITED", 7);
  ((char *)server->output->Data)[6] = ' ';
  memcpy((char *)server->output->Data + 7, server->input->Data, server->input->Size - 7);
  return 0;
}

int ProxyServerOnCommit(ProxyServer server)
{
  return SmConnectionSetData(server->connection);
}

void ProxyServerFinalize(ProxyServer server)
{
  ReleaseSmConnection(server->connection);
  ReleaseSmMemory(server->input);
  ReleaseSmMemory(server->output);
}
