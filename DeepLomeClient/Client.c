#include "pc.h"
#include <Windows.h>
#include <stdio.h>
#include "client_fb_hello_world.h"
#pragma warning(disable:4996)

int main()
{
  ProxyClient client;
  if (ProxyClientInitialize(&client) == -1) {
    printf("Error during client creation\n");
    system("pause");
    return -1;
  }

  FbHelloWorld fb_hello_world;
  if(InitializeFbHelloWorld(&fb_hello_world, client))
    printf("Error during initializing fb_hello_world\n");

  ProxyClientPrepare(client);

  fb_hello_world.input->Enable = TRUE;
  strcpy(fb_hello_world.input->Message, "Hey.That's me! #0");
  int cycle = 0;
  while (1)
  {
    if (ProxyClientOnBegin(client) == -1) {
      printf("Error during OnBegin\n");
      break;
    }
    
    Sleep(1000 + rand() % 50);

    cycle++;
    if (cycle % 10 == 0) {
      fb_hello_world.input->Message[16] = '0' + (cycle % 100) / 10;
      printf("Message changed\n");
    }

    printf("CURRENT VALID VALUE: %d\n", fb_hello_world.output->Valid);
    printf("CURRENT BUSY VALUE: %d\n", fb_hello_world.output->Busy);
    printf("-------------------------------------\n");

    if(ProxyClientOnCommit(client) == -1) {
      printf("Error during OnBegin\n");
      break;
    }
  }

  ProxyClientFinalize(client);
  system("pause");
  return 0;
}