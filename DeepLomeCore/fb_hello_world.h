#pragma once

#ifndef BOOL
#define BOOL char
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAX_MESSAGE_LENGTH 100

typedef struct {
  BOOL Enable;
  int CycleDelay;
  char Message[MAX_MESSAGE_LENGTH];
} FbHelloWorldInputData;

typedef struct {
  BOOL Valid;
  BOOL Busy;
  BOOL Error;
  int ErrorID;
} FbHelloWorldOutputData;

typedef struct {
  FbHelloWorldInputData * input;
  FbHelloWorldOutputData * output;
} FbHelloWorld;