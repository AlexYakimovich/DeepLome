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
  SmConnectionSetData(server->connection);
  return 0;
}

int ProxyServerOnCompute(ProxyServer server)
{
  sprintf(server->output->Data, "EDITED_%s", server->input->Data);
  return 0;
}

int ProxyServerOnCommit(ProxyServer server)
{
  SmConnectionGetData(server->connection);
  return 0;
}

void ProxyServerFinalize(ProxyServer server)
{
  ReleaseSmConnection(server->connection);
  ReleaseSmMemory(server->input);
  ReleaseSmMemory(server->output);
}
