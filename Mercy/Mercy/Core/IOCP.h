#pragma once

#include<Windows.h>

class IOCP
{
public:
	IOCP();
	~IOCP();

	int initializeIOCP();
	void destroyIOCP();

	HANDLE getIOCPObject() { return iocp; }
	// BOOL wait();
private:
	HANDLE iocp;
};
