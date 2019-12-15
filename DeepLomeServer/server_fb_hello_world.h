#include <stdlib.h>
#include "fb_adapter.h"
#include "fb_hello_world.h"
#include <string.h>
#pragma once

static int FbHelloWorldCreate(Fb * fb) {
  FbHelloWorld * fb_hello_world = (FbHelloWorld *)fb;
  fb_hello_world->input = malloc(sizeof(FbHelloWorldInputData));
  fb_hello_world->output = malloc(sizeof(FbHelloWorldOutputData));
  memset(fb_hello_world->input, 0, sizeof(FbHelloWorldInputData));
  memset(fb_hello_world->output, 0, sizeof(FbHelloWorldOutputData));
}

static int FbHelloWorldRelease(Fb fb) {
  free(fb.output);
  free(fb.input);
}

static int FbHelloWorldSetInput(Fb fb, Handle input) {
  memcpy(fb.input, input, sizeof(FbHelloWorldInputData));
}

static int FbHelloWorldGetOutput(Fb fb, Handle output) {
  memcpy(output, fb.output, sizeof(FbHelloWorldOutputData));
}

static int FbHelloWorldRun(Fb fb) {
  FbHelloWorldInputData * input = fb.input;
  FbHelloWorldOutputData * output = fb.output;

  if (input->Enable == TRUE)
  {
    output->Busy = TRUE;
    output->Valid = TRUE;
    printf("Message %s\n", input->Message);
  }
  else
  {
    output->Busy = FALSE;
    output->Valid = FALSE;
  }
}

FbAdapter FbHelloWorldAdapterCreate() {
  FbAdapter adapter = {
    FB_HELLO_WORLD,
    FbHelloWorldCreate,
    FbHelloWorldRelease,
    FbHelloWorldSetInput,
    FbHelloWorldGetOutput,
    FbHelloWorldRun
  };
  return adapter;
}
