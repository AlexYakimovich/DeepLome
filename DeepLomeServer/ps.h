#include "socket.h"
#include "sm_connection.h"

typedef struct {
  SmConnection connection;
  SmMemory input;
  SmMemory output;
} ProxyServerEntity;

typedef ProxyServerEntity* ProxyServer;

int ProxyServerInitialize(ProxyServer * server);

int ProxyServerOnBegin(ProxyServer server);

int ProxyServerOnCompute(ProxyServer server);

int ProxyServerOnCommit(ProxyServer server);

void ProxyServerFinalize(ProxyServer server);