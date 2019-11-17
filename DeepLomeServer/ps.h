
typedef int Socket;
typedef struct {
  Socket ServerSocket;
  Socket ClientSocket;
} ProxyServerEntity;

typedef ProxyServerEntity* ProxyServer;

int ProxyServerInitialize(ProxyServer * server);

int ProxyServerOnBegin(ProxyServer server);

int ProxyServerOnCompute(ProxyServer server);

int ProxyServerOnCommit(ProxyServer server);

void ProxyServerFinalize(ProxyServer server);