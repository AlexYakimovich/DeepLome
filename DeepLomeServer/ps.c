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


  SocketRecv(ClientSocket, &server->fbCount, sizeof(int));

  server->fbTypes = malloc(sizeof(FbType) * server->fbCount);
  server->fbs = malloc(sizeof(Fb) * server->fbCount);

  for (int i = 0; i < server->fbCount; i++)
    if (SocketRecv(ClientSocket, &server->fbTypes[i], sizeof(FbType)) != sizeof(FbType))
      return -1;


  *p_server = server;
  return 0;
}

int ProxyServerPrepare(ProxyServer server, FbAdapter * adapterList, int adapterCount)
{
  server->adapters = malloc(sizeof(FbAdapter) * adapterCount);
  memcpy(server->adapters, adapterList, sizeof(FbAdapter) * adapterCount);
  server->adaptersCount = adapterCount;

  for (int i = 0; i < server->fbCount; i++) {
    
    for (int g = 0; g < server->adaptersCount; g++) {
      if (server->fbTypes[i] == server->adapters[g].type) {
        server->adapters[g].Create(&server->fbs[i]);

        SmMemory input, output;
        InitializeSmMemory(&input, 108, SM_MEMORY_READ_ONLY);
        InitializeSmMemory(&output, 8, SM_MEMORY_WRITE_ONLY);
        memset(input->Data, 0, input->Size);
        memset(output->Data, 0, output->Size);

        AttachSmMemoryToSmConnection(server->connection, input);
        AttachSmMemoryToSmConnection(server->connection, output);
        break;
      }
    }

  }

  return 0;
}


int ProxyServerOnBegin(ProxyServer server)
{
  int fb_index = 0;
  for (int i = 0; i < server->connection->MemorySize; i++) {
    if (server->connection->Memory[i]->Type != SM_MEMORY_READ_ONLY) {
      memcpy(server->connection->Memory[i]->Data, server->fbs[fb_index].output, server->connection->Memory[i]->Size);
      fb_index++;
    }
  }
  return SmConnectionSetData(server->connection);
}

int ProxyServerOnCompute(ProxyServer server)
{
  for (int i = 0; i < server->fbCount; i++) {

    for (int g = 0; g < server->adaptersCount; g++) {
      if (server->fbTypes[i] == server->adapters[g].type) {
        server->adapters[g].Run(server->fbs[i]);
        break;
      }
    }

  }
  return 0;
}

int ProxyServerOnCommit(ProxyServer server)
{
  if (SmConnectionGetData(server->connection) == -1)
    return -1;
  int fb_index = 0;
  for (int i = 0; i < server->connection->MemorySize; i++) {
    if (server->connection->Memory[i]->Type != SM_MEMORY_WRITE_ONLY) {
      memcpy(server->fbs[fb_index].input, server->connection->Memory[i]->Data, server->connection->Memory[i]->Size);
      fb_index++;
    }
  }
  return 0;
}

void ProxyServerFinalize(ProxyServer server)
{
  ReleaseSmConnection(server->connection);/*
  ReleaseSmMemory(server->input);
  ReleaseSmMemory(server->output);*/
}
