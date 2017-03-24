#include <process.h>
#include "Thread.h"

// static
unsigned int WINAPI Thread::threadEntryFunc(void* t) {
	Thread* thread = (Thread*)t;

	if (thread->entryPoint != false) thread->entryPoint();

	return 0;
}

Thread::Thread(EntryPoint _entry) {
	entryPoint = _entry;
	maxStackSize = 0;
	beginThread();
}

Thread::Thread(EntryPoint _entry, int _maxStackSize) {
	entryPoint = _entry;
	maxStackSize = _maxStackSize;
	beginThread();
}

//
//Thread::Thread(StartDelegate _start, unsigned int _maxStackSize) {
//	start = _start;
//	maxStackSize = _maxStackSize;
//}
//
//Thread(StartDelegate _start, void* arg) {
//	startArg = _startWithArg;
//	maxStackSize = 0;
//
//}
//
//
//Thread(StartDelegate _start, void* arg, unsigned int _maxStackSize) {
//	_startWithArg
//	startArg = _startWithArg;
//	maxStackSize = _maxStackSize;
//}
//

void Thread::beginThread() {
	threadHandle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, maxStackSize, &Thread::threadEntryFunc, this, CREATE_SUSPENDED, &threadId));
}

Thread::~Thread() {
}

void Thread::start() {
	ResumeThread(threadHandle);
}

void Thread::abort() {
	BOOL ret = TerminateThread(threadHandle, (DWORD)-1);
	if (ret == false) {
		// DWORD err = GetLastError();
		// todo : log err
	}
	threadHandle = NULL;
}

void Thread::resume() {
	ResumeThread(threadHandle);
}

bool Thread::suspend() {
	if (threadHandle == NULL) {
		// todo : log
		return false;
	}

	DWORD ret = SuspendThread(threadHandle);
	if (ret == -1) {
		// todo : log
		return false;
	}
	return true;
}
