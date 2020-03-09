#include "../thread.h"
#include <Windows.h>

ThreadHandle OsalThreadCreate(ThreadFunction func, ThreadArgs args)
{
  ThreadHandle handle;
  CreateThread(NULL, 0, func, args, NULL, &handle);
  return handle;
}

int OsalThreadJoin(ThreadHandle handle)
{
  return WaitForSingleObject(handle, INFINITE);
}

int OsalSleep(int ms) {
  Sleep(ms);
}

EventHandle EventCreate(char manualReset, char initialValue) {
  return CreateEvent(NULL, manualReset, initialValue, NULL);
}

int EventDestroy(EventHandle handle) {
  return CloseHandle(handle);
}

int EventSet(EventHandle handle) {
  SetEvent(handle);
}

int EventWait(EventHandle handle, int timeout) {
  return WaitForSingleObject(handle, timeout);
}