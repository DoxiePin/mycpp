//#pragma once
//
//#include<WinSock2.h>
//#include"IOCP.h"
//
//#define BUFFER_SIZE 1024
//
//class PerIoData : OVERLAPPED {
//public:
//	enum IoType {
//		send,
//		recv,
//	};
//
//	PerIoData();
//	~PerIoData();
//
//	IoType ioType;
//	void setupWSABuffer();
//	WSABUF wsaBuffer;
//private:
//	
//	char buffer[BUFFER_SIZE];
//	int bufferPosition;
//};
//
//class TcpSession
//{
//public:
//	TcpSession();
//	~TcpSession();
//	SOCKET clientSocket;
//	SOCKADDR_IN clientAddr;
//
//	HANDLE bindIOCP(IOCP* iocp);
//	int receve();
//
//private:
//	PerIoData receiveData;
//};
