#include "pc.h"
#include <stdio.h>
#include <string.h>


int ProxyClientInitialize(ProxyClient * p_client)
{
  ProxyClient client = malloc(sizeof(ProxyClientEntity));

  client->ClientSocket = SocketCreate();
  if (SocketConnect(client->ClientSocket, 1337, INADDR_LOOPBACK) == -1)
    return -1;

  InitializeSmConnection(&client->connection, client->ClientSocket);
  client->fbCount = 0;

  *p_client = client;
  return 0;
}
int ProxyClientPrepare(ProxyClient client)
{
  SocketSend(client->ClientSocket, &client->fbCount, sizeof(int));
  for(int i = 0; i < client->fbCount; i++)
    SocketSend(client->ClientSocket, &client->fb_types[i], sizeof(FbType));
  return 0;
}
static int iter = 0;

int ProxyClientOnBegin(ProxyClient client)
{
  if (SmConnectionGetData(client->connection) == -1)
    return -1;
  return 0;
}


int ProxyClientOnCommit(ProxyClient client)
{
  if (SmConnectionSetData(client->connection) == -1)
    return -1;
  return 0;
}

int ProxyClientInitializeFb(Fb * fb, FbType type, int input_size, int output_size, ProxyClient client)
{
  SmMemory input, output;
  InitializeSmMemory(&input, input_size, SM_MEMORY_WRITE_ONLY);
  InitializeSmMemory(&output, output_size, SM_MEMORY_READ_ONLY);
  memset(input->Data, 0, input->Size);
  memset(output->Data, 0, output->Size);

  AttachSmMemoryToSmConnection(client->connection, input);
  AttachSmMemoryToSmConnection(client->connection, output);

  fb->input = input->Data;
  fb->output = output->Data;

  client->fb_types[client->fbCount] = type;
  client->fbCount++;
  return 0;
}

void ProxyClientFinalize(ProxyClient client)
{
  free(client);
}
