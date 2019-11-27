#include "pc.h"


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

int ProxyClientOnBegin(ProxyClient client)
{
  SmConnectionGetData(client->connection);
  printf("%s\n", client->output->Data);
  return 0;
}
static int iter = 0;

int ProxyClientOnCommit(ProxyClient client)
{
  char msg[] = "OFF BEGIN #0";
  msg[11] = '0' + iter % 10;
  iter++;
  memcpy(client->input->Data, msg, sizeof(msg));
  SmConnectionSetData(client->connection);
}

void ProxyClientFinalize(ProxyClient client)
{
  free(client);
}
