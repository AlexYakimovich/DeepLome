#pragma once
#include "fb_hello_world.h"
#include "pc.h"
#include <stdlib.h>

int InitializeFbHelloWorld(FbHelloWorld * fb, ProxyClient client) {
  ProxyClientInitializeFb((Fb *)fb, FB_HELLO_WORLD, sizeof(FbHelloWorldInputData), sizeof(FbHelloWorldOutputData), client);
}