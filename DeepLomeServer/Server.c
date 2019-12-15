#include <stdio.h>
#include "ps.h"
#include "server_fb_hello_world.h"

int main()
{
  printf("Waiting for a client...\n");
  ProxyServer server;
  ProxyServerInitialize(&server);
  printf("Client connected\n");

  FbAdapter adapters[] = {FbHelloWorldAdapterCreate()};
  ProxyServerPrepare(server, adapters, sizeof(adapters) / sizeof(adapters[0]));

  while (1)
  {
    if(ProxyServerOnBegin(server) == -1)
      return -1;

    if (ProxyServerOnCompute(server))
      return -2;

    if (ProxyServerOnCommit(server))
      return -3;
  }

  system("pause");
  return 0;
}