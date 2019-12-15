#include "socket.h"
#include "sm_connection.h"
#include "fb_types.h"
#pragma once
#define MAX_INITIALIZED_FB 100

typedef char Byte;

typedef struct {
  Socket ClientSocket;
  SmConnection connection;
  FbType fb_types[MAX_INITIALIZED_FB];
  int fbCount;
} ProxyClientEntity;

typedef ProxyClientEntity* ProxyClient;

int ProxyClientInitialize(ProxyClient * client);

int ProxyClientPrepare(ProxyClient client);

int ProxyClientOnBegin(ProxyClient client);

int ProxyClientOnCommit(ProxyClient client);

int ProxyClientInitializeFb(Fb * fb, FbType type, int input_size, int output_size, ProxyClient client);

void ProxyClientFinalize(ProxyClient client);