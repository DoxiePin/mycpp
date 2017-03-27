#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&cs);
}

CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&cs);
}

void CriticalSection::enterLock() {
	EnterCriticalSection(&cs);
}

void CriticalSection::leaveLock() {
	LeaveCriticalSection(&cs);
}
