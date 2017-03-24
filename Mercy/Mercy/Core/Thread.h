#pragma once

#include "../3rdParty\delegate.hpp"
#include <windows.h>

using namespace srutil;

typedef delegate<int()> EntryPoint;

class Thread
{
private:
	static unsigned int WINAPI threadEntryFunc(void* t);

public:
	Thread::Thread(EntryPoint _entry);
	Thread::Thread(EntryPoint _entry, int _maxStackSize);
	~Thread();

	void start();
	void abort();
	void resume();
	bool suspend();

	//bool isAlive();
	//void join();
	//void priority();
	//void threadState();

private:
	void beginThread();

	EntryPoint entryPoint;
	unsigned int maxStackSize;
	unsigned int threadId;
	HANDLE threadHandle;
};

