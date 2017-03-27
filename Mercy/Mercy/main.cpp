#include<WinSock2.h>
#include <iostream>
#include <vector>
#include "3rdParty/delegate.hpp"
#include "Core/Thread.h"
#include "Core/IOCP.h"
#include "Core/CriticalSection.h"

#include "TcpSession.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int echoThreadMain();
void createThreads();
//void listen();
vector<Thread*> threads;
int wsaStartup();
IOCP* iocp = new IOCP();
TcpSession session;

//TcpSession* accept();
//
//SOCKET serverSocket;
//

TcpSession serverSession;

CriticalSection cs;

int main() {
	int result;

	result = iocp->initializeIOCP();
	if (result != 1) return -1;

	createThreads();

	result = wsaStartup();
	if (result != 0) return result;
	serverSession.create(iocp);
	serverSession.bind(9091);
	serverSession.listen(5);

	while (true) {
		Sleep(1000);
//		TcpSession* session = accept();
//		session->bindIOCP(iocp);
//		session->receve();
	}
//
//	cout << "init success" << endl;
//
	return 0;
}


int wsaStartup() {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "error" << endl;
		return -1;
	}
	return 0;
}

void createThreads() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	for (DWORD i = 0; i < sysinfo.dwNumberOfProcessors; i++) {
		Thread* thread = new Thread(EntryPoint::from_function<&echoThreadMain>());
		thread->start();
		threads.push_back(thread);
	}
}

//TcpSession* accept() {
//	int addrLen = sizeof(SOCKADDR_IN);
//	TcpSession* session = new TcpSession();
//	session->clientSocket = accept(serverSocket, (SOCKADDR*)&session->clientAddr, &addrLen);
//	return session;
//}
//

int echoThreadMain() {
	// IOCP* iocp = (IOCP*)compPort;
	static int i = 0;
	int j;
	lock(cs) {
		j = i;
		i++;
	}

	while (true) {
		lock(cs) {
			cout << "this is " << j << endl;
		}
			
		//TcpSession* session = NULL;
		//BOOL val = iocp->wait();

		// BOOL val = GetQueuedCompletionStatus(compPort, &bytesTrans, (LPDWORD)session, (LPOVERLAPPED*)&ioInfo, INFINITE);
		//socket = session->clientSocket;
		//if (ioInfo->rwMode == READ) {
		//	if (bytesTrans == 0) {
		//		closesocket(socket);
		//		delete session;
		//		free(ioInfo);
		//		continue;
		//	}
		//	memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		//	ioInfo->wsaBuffer.len = bytesTrans;
		//	// ioInfo->rwMode = WRITE;

		//	WSASend(socket, &(ioInfo->wsaBuffer), 1, NULL, 0, &(ioInfo->overlapped), NULL);

		//	ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		//	memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		//	ioInfo->wsaBuffer.len = 100;
		//	ioInfo->wsaBuffer.buf = ioInfo->buffer;
		//	ioInfo->rwMode = READ;
		//	WSARecv(socket, &(ioInfo->wsaBuffer), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
		//} else {
		//	free(ioInfo);
		//}

	}
	return 0;
}