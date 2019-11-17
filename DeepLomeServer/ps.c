#include "ps.h"
#include <stdio.h>
#include <winsock.h>
#pragma comment(lib,"WS2_32")
#pragma warning(disable:4996)

static char initialized = FALSE;

static void InitializeWSA()
{
  if (initialized)
    return;
  initialized = TRUE;
  int iResult;
  WSADATA wsaData;
  // Initialize Winsock
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    printf("WSAStartup failed: %d\n", iResult);
  }
}


int ProxyServerInitialize(ProxyServer * server)
{
  InitializeWSA();
  ProxyServerEntity inst = {
    socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
  };
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(1337);
  SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(inst.ServerSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));

  listen(inst.ServerSocket, SOMAXCONN);

  inst.ClientSocket = accept(inst.ServerSocket, 0, 0);

  *server = malloc(sizeof(ProxyServerEntity));

  memcpy(*server, &inst, sizeof(ProxyServerEntity));
  return 0;
}

int ProxyServerOnBegin(ProxyServer server)
{
  char msg[] = "ON COMMIT";
  send(server->ClientSocket, msg, sizeof(msg), NULL);
  return 0;
}

int ProxyServerOnCompute(ProxyServer server)
{
  return 0;
}

int ProxyServerOnCommit(ProxyServer server)
{
  char msg[10];
  recv(server->ClientSocket, msg, 10, NULL);
  printf("%s\n", msg);
  return 0;
}

void ProxyServerFinalize(ProxyServer server)
{
}
