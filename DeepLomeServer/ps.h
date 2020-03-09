#include "../DeepLomeCore/socket.h"
#include "../DeepLomeCore/sm_connection.h"
#include "../DeepLomeCore/fb_types.h"
#include "../DeepLomeCore/fb_adapter.h"
#include "../DeepLomeCore/thread.h"
#define MAX_CONNECTION_COUNT 5
#define MAX_FB_COUNT 100

typedef struct {
  EventHandle syncEvent;
  SmConnection connections[5];
  int connectionCount;
  FbType fbTypes[MAX_FB_COUNT];
  Fb fbs[MAX_FB_COUNT];
  int fbCount;
  FbAdapter * adapters;
  int adaptersCount;
} ProxyServerEntity;

typedef ProxyServerEntity* ProxyServer;

int ProxyServerWaitForSubscribers(ProxyServer server);

int ProxyServerInitialize(ProxyServer * server);

int ProxyServerPrepare(ProxyServer server, FbAdapter * adapterList, int adapterCount);

int ProxyServerOnBegin(ProxyServer server);

int ProxyServerOnCompute(ProxyServer server);

int ProxyServerOnCommit(ProxyServer server);

void ProxyServerFinalize(ProxyServer server);