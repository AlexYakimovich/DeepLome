#include "ps.h"
#include <stdio.h>


int main()
{
  ProxyServer server;
  ProxyServerInitialize(&server);
  while (1)
  {
    ProxyServerOnBegin(server);

    ProxyServerOnCompute(server);

    ProxyServerOnCommit(server);
  }

  system("pause");
  return 0;
}