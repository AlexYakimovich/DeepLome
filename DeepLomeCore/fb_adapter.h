#pragma once
#include "fb_types.h"

typedef int(*FbCreate)(Fb * fb);
typedef int(*FbRelease)(Fb fb);
typedef int(*FbSetInputParam)(Fb fb, Handle);
typedef int(*FbGetOutputParam)(Fb fb, Handle);
typedef int(*FbRun)(Fb);

typedef struct {
  FbType type;
  FbCreate Create;
  FbRelease Release;
  FbSetInputParam SetInputParam;
  FbGetOutputParam GetOutputParam;
  FbRun Run;
} FbAdapter;