
typedef int Socket;
typedef struct {
  Socket ClientSocket;
} ProxyClientEntity;

typedef ProxyClientEntity* ProxyClient;

int ProxyClientInitialize(ProxyClient * client);

int ProxyClientOnBegin(ProxyClient client);

int ProxyClientOnCommit(ProxyClient client);

void ProxyClientFinalize(ProxyClient client);