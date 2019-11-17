#include "pc.h"
#include <Windows.h>
#include <stdio.h>
int main()
{
  ProxyClient client;
  ProxyClientInitialize(&client);

  while (1)
  {
    ProxyClientOnBegin(client);

    Sleep(500 + rand() % 1500);

    ProxyClientOnCommit(client);
  }


  printf("Hello world from client!\n");
  system("pause");
  return 0;
}