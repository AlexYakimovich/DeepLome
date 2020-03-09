#include "../socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#pragma comment(lib,"WS2_32")
#pragma warning(disable:4996)


Socket SocketCreate()
{
  Socket sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  return sock;
}

int SocketConnect(Socket sock, int port, int ip_addr)
{
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(port);
  SockAddr.sin_addr.s_addr = htonl(ip_addr);

  return connect(sock, (struct sockaddr *)&SockAddr, sizeof(SockAddr));
}

int SocketBind(Socket sock, int port, int ip_addr)
{
  int result;
  struct sockaddr_in SockAddr;
  SockAddr.sin_family = AF_INET;
  SockAddr.sin_port = htons(1337);
  SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (0 != (result = bind(sock, (struct sockaddr *)(&SockAddr), sizeof(SockAddr))))
    return result;

  if (0 != (result = listen(sock, SOMAXCONN)))
    return result;

  return 0;
}

Socket SocketAccept(Socket sock)
{
  return accept(sock, NULL, 0);
}

int SocketSend(Socket sock, Memory data, unsigned int size)
{
  return send(sock, (char *)data, size, 0);
}

int SocketRecv(Socket sock, Memory data, unsigned int size)
{
  return recv(sock, (char *)data, size, 0);
}

void SocketClose(Socket sock)
{
  close(sock);
}
