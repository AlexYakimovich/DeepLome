#include "socket.h"
#include "sm_connection.h"

typedef struct {
  SmConnection connection;
  SmMemory input;
  SmMemory output;
} ProxyClientEntity;

typedef ProxyClientEntity* ProxyClient;

int ProxyClientInitialize(ProxyClient * client);

int ProxyClientOnBegin(ProxyClient client);

int ProxyClientOnCommit(ProxyClient client);

void ProxyClientFinalize(ProxyClient client);