#pragma once

#include<Windows.h>

class CriticalSection
{
private:
	CRITICAL_SECTION cs;

public:
	CriticalSection();
	~CriticalSection();

	void enterLock();
	void leaveLock();
};

template<class T>
class LockHelper {
private:
	T* lockTarget;
public:
	operator int() const { return 0; }
	explicit LockHelper(T* _lockTarget) : lockTarget(_lockTarget) { lockTarget->enterLock(); }
	explicit LockHelper(T& _lockTarget) : lockTarget(&_lockTarget) { lockTarget->enterLock(); }
	~LockHelper() { lockTarget->leaveLock(); }
};

#define lock(lock) if(LockHelper<CriticalSection> __lock = LockHelper<CriticalSection>(lock)) __assume(0); else
