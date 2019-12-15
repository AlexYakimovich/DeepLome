#include "socket.h"
#include "sm_connection.h"
#include "fb_types.h"
#include "fb_adapter.h"

typedef struct {
  SmConnection connection;
  FbType * fbTypes;
  Fb * fbs;
  int fbCount;
  FbAdapter * adapters;
  int adaptersCount;
} ProxyServerEntity;

typedef ProxyServerEntity* ProxyServer;

int ProxyServerInitialize(ProxyServer * server);

int ProxyServerPrepare(ProxyServer server, const FbAdapter * adapterList, int adapterCount);

int ProxyServerOnBegin(ProxyServer server);

int ProxyServerOnCompute(ProxyServer server);

int ProxyServerOnCommit(ProxyServer server);

void ProxyServerFinalize(ProxyServer server);