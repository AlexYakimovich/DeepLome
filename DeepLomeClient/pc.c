#include "pc.h"
#include <stdio.h>


int ProxyClientInitialize(ProxyClient * p_client)
{
  ProxyClient client = malloc(sizeof(ProxyClientEntity));

  Socket ClientSocket = SocketCreate();
  SocketConnect(ClientSocket, 1337, INADDR_LOOPBACK);

  InitializeSmConnection(&client->connection, ClientSocket);
  InitializeSmMemory(&client->input, 40, SM_MEMORY_WRITE_ONLY);
  InitializeSmMemory(&client->output, 40, SM_MEMORY_READ_ONLY);

  AttachSmMemoryToSmConnection(client->connection, client->input);
  AttachSmMemoryToSmConnection(client->connection, client->output);

  *p_client = client;
  return 0;
}
static int iter = 0;

int ProxyClientOnBegin(ProxyClient client)
{

  char msg[] = "OFF BEGIN #0";
  msg[11] = '0' + iter % 10;
  printf("SEND %s\n", msg);
  iter++;
  memcpy(client->input->Data, msg, client->input->Size);
  if(SmConnectionSetData(client->connection) == -1)
    printf("ERROR SET\n");
  return 0;
}


int ProxyClientOnCommit(ProxyClient client)
{
  if(SmConnectionGetData(client->connection) == -1)
    printf("ERROR GET\n");
  printf("%s\n", client->output->Data);
}

void ProxyClientFinalize(ProxyClient client)
{
  free(client);
}
