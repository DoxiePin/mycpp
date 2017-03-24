//#include "TcpSession.h"
//
//TcpSession::TcpSession()
//{
//}
//
//TcpSession::~TcpSession()
//{
//}
//
//HANDLE TcpSession::bindIOCP(IOCP* iocp) {
//	return CreateIoCompletionPort((HANDLE)this->clientSocket, iocp->getIOCPObject(), (DWORD)this, 0);
//}
//
//int TcpSession::receve()
//{
//	memset(&receiveData, 0, sizeof(OVERLAPPED));
//	receiveData.setupWSABuffer();
//	receiveData.ioType = PerIoData::IoType::recv;
//
//	int recvBytes;
//	int flags = 0;
//	return WSARecv(this->clientSocket, &(receiveData.wsaBuffer), 1, (DWORD*)&recvBytes, (DWORD*)&flags, (LPWSAOVERLAPPED)&receiveData, NULL);
//}
//
//PerIoData::PerIoData() {
//	bufferPosition = 0;
//}
//
//PerIoData::~PerIoData() {}
//
//void PerIoData::setupWSABuffer() {
//	int bufferLength = BUFFER_SIZE - bufferPosition;
//	wsaBuffer.len = bufferLength;
//	wsaBuffer.buf = &buffer[bufferPosition];
//}
