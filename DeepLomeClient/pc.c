#include "pc.h"
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


int ProxyClientInitialize(ProxyClient * client)
{
  InitializeWSA();
  const ProxyClientEntity inst = {
    socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
  };
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(1337);
  SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  connect(inst.ClientSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr));

  *client = malloc(sizeof(ProxyClientEntity));

  memcpy(*client, &inst, sizeof(ProxyClientEntity));
  return 0;
}

int ProxyClientOnBegin(ProxyClient client)
{
  char msg[10];
  recv(client->ClientSocket, msg, sizeof(msg), NULL);
  printf("%s\n", msg);
  return 0;
}

int ProxyClientOnCommit(ProxyClient client)
{
  char msg[] = "OFF BEGIN";
  return send(client->ClientSocket, msg, sizeof(msg), NULL) > 0;
}

void ProxyClientFinalize(ProxyClient client)
{
  closesocket(client->ClientSocket);
  free(client);
}
