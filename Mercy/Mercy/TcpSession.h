#pragma once

#include<WinSock2.h>
#include"Core\CriticalSection.h"

class IOCP;
class CriticalSection;

#define BUFFER_SIZE 1024

class PerIoData : OVERLAPPED {
public:
	enum IoType {
		send,
		recv,
		accept,
		disconnect,
	};

	PerIoData();
	~PerIoData();

	IoType ioType;
	void setupWSABuffer();
	WSABUF wsaBuffer;
private:
	
	char buffer[BUFFER_SIZE];
	int bufferPosition;
};

class TcpSession
{
public:
	enum SessionState {
		notCreated,
		notConnected,
		listening,
		connecting,
		connected,
		disconnecting,
		disconnected,
	};

	TcpSession();
	~TcpSession();

	SOCKET socket;
	CriticalSection socketLock;
	SOCKADDR_IN addr;

	SessionState sessionState;
	CriticalSection stateLock;

	void setState(SessionState newState);
	
	HANDLE bindIOCP(IOCP* iocp);
	bool create(IOCP* iocp);
	void close();

	bool bind(int port);
	bool listen(int backlog);

	bool reqestAccept();
	int reqestReceive();
	int reqestSend();
	int reqestDisconnect();

private:
	PerIoData receiveData;
};
