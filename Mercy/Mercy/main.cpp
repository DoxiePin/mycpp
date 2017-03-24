#include <iostream>
#include "3rdParty\delegate.hpp"
using namespace srutil;

typedef delegate2<void, int, int> mydel;

mydel del;


void testFunc(int a, int b) {
	std::cout << a + b;
}

int main() {
	del = mydel::from_function<&testFunc>();
	del(20, 30);

	return -1;
}

//#include<WinSock2.h>
//#include<process.h>
//#include<iostream>
//
//#include "TcpSession.h"
//#include "IOCP.h"
//
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//unsigned int WINAPI EchoThreadMain(LPVOID compPort);
//void createThreads(IOCP* iocp);
//void listen();
//int wsaStartup();
//
//TcpSession* accept();
//
//SOCKET serverSocket;
//
//int main() {
//	int result;
//
//	result = wsaStartup();
//	if (result != 0) return result;
//
//	IOCP* iocp = new IOCP();
//	result = iocp->initializeIOCP();
//	if (result != 1) return -1;
//
//	createThreads(iocp);
//	listen();
//	
//	while (true) {
//		TcpSession* session = accept();
//		session->bindIOCP(iocp);
//		session->receve();
//	}
//
//	cout << "init success" << endl;
//
//	return 0;
//}
//
//int wsaStartup() {
//	WSADATA wsaData;
//	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (result != 0) {
//		cout << "error" << endl;
//		return -1;
//	}
//	return 0;
//}
//
//void createThreads(IOCP* iocp) {
//	SYSTEM_INFO sysinfo;
//	GetSystemInfo(&sysinfo);
//	for (DWORD i = 0; i < sysinfo.dwNumberOfProcessors; i++) {
//		_beginthreadex(NULL, 0, EchoThreadMain, (LPVOID)iocp, 0, NULL);
//	}
//}
//
//void listen() {
//	SOCKADDR_IN serverAddr;
//	serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
//	memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(9191);
//
//	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
//	listen(serverSocket, 5);
//}
//
//TcpSession* accept() {
//	int addrLen = sizeof(SOCKADDR_IN);
//	TcpSession* session = new TcpSession();
//	session->clientSocket = accept(serverSocket, (SOCKADDR*)&session->clientAddr, &addrLen);
//	return session;
//}
//
//unsigned int WINAPI EchoThreadMain(LPVOID compPort) {
//	IOCP* iocp = (IOCP*)compPort;
//
//	while (true) {
//		TcpSession* session = NULL;
//		BOOL val = iocp->wait();
//
//		// BOOL val = GetQueuedCompletionStatus(compPort, &bytesTrans, (LPDWORD)session, (LPOVERLAPPED*)&ioInfo, INFINITE);
//		//socket = session->clientSocket;
//		//if (ioInfo->rwMode == READ) {
//		//	if (bytesTrans == 0) {
//		//		closesocket(socket);
//		//		delete session;
//		//		free(ioInfo);
//		//		continue;
//		//	}
//		//	memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
//		//	ioInfo->wsaBuffer.len = bytesTrans;
//		//	// ioInfo->rwMode = WRITE;
//
//		//	WSASend(socket, &(ioInfo->wsaBuffer), 1, NULL, 0, &(ioInfo->overlapped), NULL);
//
//		//	ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
//		//	memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
//		//	ioInfo->wsaBuffer.len = 100;
//		//	ioInfo->wsaBuffer.buf = ioInfo->buffer;
//		//	ioInfo->rwMode = READ;
//		//	WSARecv(socket, &(ioInfo->wsaBuffer), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
//		//} else {
//		//	free(ioInfo);
//		//}
//
//	}
//	return 0;
//}