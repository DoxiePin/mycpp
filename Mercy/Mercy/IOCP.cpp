#include "IOCP.h"
#include "TcpSession.h"

IOCP::IOCP()
{
}


IOCP::~IOCP()
{
}

int IOCP::initializeIOCP() {
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	return 1;
}

void IOCP::destroyIOCP() {

}

BOOL IOCP::wait() {
	DWORD bytesTrans;
	TcpSession* session = NULL;
	PerIoData ioData;
	SOCKET socket;
	DWORD flags = 0;

	bool result = GetQueuedCompletionStatus(iocp, &bytesTrans, (LPDWORD)session, (LPOVERLAPPED*)&ioData, INFINITE);
	if (result == false) {
		// todo : get last error.
		// destroy resorces
		return false;
	}

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