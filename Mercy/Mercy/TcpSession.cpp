#include "TcpSession.h"
#include "Core/IOCP.h"

PerIoData::PerIoData() {
	bufferPosition = 0;
}

PerIoData::~PerIoData() {}

void PerIoData::setupWSABuffer() {
	int bufferLength = BUFFER_SIZE - bufferPosition;
	wsaBuffer.len = bufferLength;
	wsaBuffer.buf = &buffer[bufferPosition];
}

TcpSession::TcpSession()
{
}

TcpSession::~TcpSession()
{
}

HANDLE TcpSession::bindIOCP(IOCP* iocp) {
	if (iocp == NULL) {
		return NULL;
	}

	return CreateIoCompletionPort((HANDLE)socket, iocp->getIOCPObject(), (DWORD)this, 0);
}

void TcpSession::setState(SessionState newState) {
	lock(stateLock) {
		sessionState = newState;
	}
}

bool TcpSession::create(IOCP* iocp) {
	lock(socketLock) {
		if (socket != INVALID_SOCKET) {
			close();
		}
		socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
		HANDLE handle = bindIOCP(iocp);
		if (handle == NULL) {
			return false;
		}
		if (socket == INVALID_SOCKET) {
			setState(SessionState::notCreated);
			return false;
		}
	}
	setState(SessionState::notConnected);
	return true;
}

void TcpSession::close() {
	lock(socketLock) {
		if (INVALID_SOCKET != socket) {
			closesocket(socket);
			socket = INVALID_SOCKET;
			setState(SessionState::notCreated);
		}
	}
}

bool TcpSession::bind(int port) {
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int ret;
	ret = ::bind(socket, (const sockaddr*)&addr, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret) {
		return false;
	}

	return true;
}

bool TcpSession::listen(int backlog) {
	setState(SessionState::listening);
	int ret = ::listen(socket, backlog);
	if (SOCKET_ERROR == ret) {
		return false;
	}
	return true;
}

bool TcpSession::reqestAccept() {
	
}

//int TcpSession::receve()
//{
//	memset(&receiveData, 0, sizeof(OVERLAPPED));
//	receiveData.setupWSABuffer();
//	receiveData.ioType = PerIoData::IoType::recv;
//
//	int recvBytes;
//	int flags = 0;
//	return WSARecv(socket, &(receiveData.wsaBuffer), 1, (DWORD*)&recvBytes, (DWORD*)&flags, (LPWSAOVERLAPPED)&receiveData, NULL);
//}
