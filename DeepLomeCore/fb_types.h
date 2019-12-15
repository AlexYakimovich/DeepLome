#pragma once

typedef void* Handle;

typedef struct {
  Handle * input;
  Handle * output;
} Fb;

typedef enum
{
  FB_HELLO_WORLD = 1
} FbType;