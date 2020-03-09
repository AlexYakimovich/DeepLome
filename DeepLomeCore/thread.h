#pragma once
#define INFINITE            0xFFFFFFFF  // Infinite timeout
typedef void* ThreadArgs;
typedef void* ThreadHandle;
typedef void* EventHandle;
typedef void*(*ThreadFunction)(ThreadArgs);

ThreadHandle OsalThreadCreate(ThreadFunction func, ThreadArgs args);

int OsalThreadJoin(ThreadHandle handle);

int OsalSleep(int ms);

EventHandle EventCreate(char manualReset, char initialValue);

int EventDestroy(EventHandle handle);

int EventSet(EventHandle handle);

int EventWait(EventHandle handle, int timeout);