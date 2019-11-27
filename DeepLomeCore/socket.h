#ifndef NULL
#define NULL (void*)0
#endif

#ifndef INADDR_ANY
#define INADDR_ANY              (unsigned long)0x00000000
#endif

#ifndef INADDR_LOOPBACK
#define INADDR_LOOPBACK         0x7f000001
#endif

typedef int Socket;
typedef void* Memory;

Socket SocketCreate();

int SocketConnect(Socket sock, int port, int ip_addr);

int SocketBind(Socket sock, int port, int ip_addr);

Socket SocketAccept(Socket sock);

int SocketSend(Socket sock, Memory data, unsigned int size);

int SocketRecv(Socket sock, Memory data, unsigned int size);

void SocketClose(Socket sock);