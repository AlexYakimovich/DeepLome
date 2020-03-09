#include "ps.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma warning(disable : 4996)

int ProxyServerWaitForSubscribers(ProxyServer server)
{
  while (server->connectionCount < 1)
    OsalSleep(100);
  return 0;
}

static void AcceptFunc(ProxyServer server) {

  Socket MasterSocket = SocketCreate();
  SocketBind(MasterSocket, 1337, INADDR_ANY);

  while (1) {
    Socket ClientSocket = SocketAccept(MasterSocket);
    EventWait(server->syncEvent, INFINITE);
    InitializeSmConnection(&server->connections[server->connectionCount], ClientSocket);

    int fbCount;
    SocketRecv(ClientSocket, &fbCount, sizeof(int));
    
    for (int i = server->fbCount; i < server->fbCount + fbCount; i++) {
      if (SocketRecv(ClientSocket, &server->fbTypes[i], sizeof(FbType)) != sizeof(FbType))
        return -1;
      for (int g = 0; g < server->adaptersCount; g++) {
        if (server->fbTypes[i] == server->adapters[g].type) {
          server->adapters[g].Create(&server->fbs[i]);

          SmMemory input, output;
          InitializeSmMemory(&input, 108, SM_MEMORY_READ_ONLY);
          InitializeSmMemory(&output, 8, SM_MEMORY_WRITE_ONLY);
          memset(input->Data, 0, input->Size);
          memset(output->Data, 0, output->Size);

          AttachSmMemoryToSmConnection(server->connections[server->connectionCount], input);
          AttachSmMemoryToSmConnection(server->connections[server->connectionCount], output);
          break;
        }
      }
    }
    printf("Fbs initialized");

    server->fbCount += fbCount;
    server->connectionCount++;
    EventSet(server->syncEvent);
  }
}

int ProxyServerInitialize(ProxyServer * p_server)
{
  ProxyServer server = malloc(sizeof(ProxyServerEntity));
  server->connectionCount = 0;
  server->fbCount = 0;
  server->syncEvent = EventCreate(0, 1);
  ThreadHandle hAcceptor = OsalThreadCreate(AcceptFunc, server);

  *p_server = server;
  return 0;
}

int ProxyServerPrepare(ProxyServer server, FbAdapter * adapterList, int adapterCount)
{
  server->adapters = malloc(sizeof(FbAdapter) * adapterCount);
  memcpy(server->adapters, adapterList, sizeof(FbAdapter) * adapterCount);
  server->adaptersCount = adapterCount;

  return 0;
}


int ProxyServerOnBegin(ProxyServer server)
{
  EventWait(server->syncEvent, INFINITE);
  int result;
  int fb_index = 0;
  for (int connectionID = 0; connectionID < server->connectionCount; connectionID++) {
    for (int i = 0; i < server->connections[connectionID]->MemorySize; i++) {
      if (server->connections[connectionID]->Memory[i]->Type != SM_MEMORY_READ_ONLY) {
        memcpy(server->connections[connectionID]->Memory[i]->Data, server->fbs[fb_index].output, server->connections[connectionID]->Memory[i]->Size);
        fb_index++;
      }
    }
    if ((result = SmConnectionSetData(server->connections[connectionID])) != 0)
      return result;
  }
  return 0;
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
  int fb_index = 0;
  for (int connectionID = 0; connectionID < server->connectionCount; connectionID++) {
    if (SmConnectionGetData(server->connections[connectionID]) == -1)
      return -1;
    for (int i = 0; i < server->connections[connectionID]->MemorySize; i++) {
      if (server->connections[connectionID]->Memory[i]->Type != SM_MEMORY_WRITE_ONLY) {
        memcpy(server->fbs[fb_index].input, server->connections[connectionID]->Memory[i]->Data, server->connections[connectionID]->Memory[i]->Size);
        fb_index++;
      }
    }
  }
  EventSet(server->syncEvent);
  return 0;
}

void ProxyServerFinalize(ProxyServer server)
{
  for(int connectionID = 0; connectionID < server->connectionCount; connectionID++)
    ReleaseSmConnection(server->connections[connectionID]);
  /*ReleaseSmMemory(server->input);
  ReleaseSmMemory(server->output);*/
}
