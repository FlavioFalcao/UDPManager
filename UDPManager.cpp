/*
 * UDPManager.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: Catur Wirawan W
 *
 *      UDP Manager untuk penanganan UDP
 */

#include "UDPManager.h"

bool UDPManager::m_bWinsockInit = false;

UDPManager::UDPManager(){
	//winsock initialized
	#ifdef TARGET_WIN32
		if(!m_bWinsockInit){
			unsigned short vr;
			WSADATA wsadata;
			vr = MAKEWORD(2,2);
			WSAStartup(vr, &wsaData);
			m_bWinsockInit = true;

		}
	#endif

	m_hSocket = INVALID_SOCKET;
	m_dwTimeoutReceive = UDP_DEFAULT_TIMEOUT;
	m_iListenPort = -1;
}

bool UDPManager::Close(){
	if (m_hSocket == INVALID_SOCKET){
		return false;
	}

	#ifdef TARGET_WIN32
		if(closesocket(m_hSocket) == SOCKET_ERROR)
	#else
		if(close(m_hSocket) == SOCKET_ERROR)
	#endif
	{
		//FIXME 1. add loggger or something
	}

	m_hSocket = INVALID_SOCKET;
	return true;
}

bool UDPManager::Create(){
	if(m_hSocket != INVALID_SOCKET){
		return false;
	}
	m_hSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_hSocket != INVALID_SOCKET){
		int unused = true;
		setsockopt(m_hSocket,SOL_SOCKET, SO_REUSEADDR, (char*)&unused, sizeof(unused));
	}
	bool ret = m_hSocket != INVALID_SOCKET;
	if(!ret){
		//FIXME 1. add logger or something
	}
	return ret;
}

bool UDPManager::Connect(const char *pHost, unsigned short usPort){
	memset(&saClient, 0, sizeof(sockaddr_in));
	struct hostent *he;

	if(m_hSocket == INVALID_SOCKET){
		return false;
	}

	if((he = gethostbyname(pHost)) == NULL){
		return false;
	}

	saClient.sin_family = AF_INET; //host byte order
	saClient.sin_port = htons(usPort);

	memcpy((char*)&saClient.sin_addr.s_addr, he->h_addr_list[0],he->h_length);

	memset(&(saClient.sin_zero),'\0',8);

	return true;
}

bool UDPManager::ConnectMcast(char *pMcast, unsigned short usPort){
	//assocaite source socket address dengan socket
	if(!Bind(usPort)){
		//FIXME
		return false;
	}

	if(!(SetTTL(1))){
		//FIXME
	}

	if(!Connect(pMcast, usPort)){
		//FIXME
		return false;
	}

	return true;
}

bool UDPManager::Bind(unsigned short usPort){
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;
	saServer.sin_port = htons(usPort);

	int ret = bind(m_hSocket, (struct sockaddr*)&saServer, sizeof(struct sockaddr));
	if(ret == -1){
		//FIXME do somehting logger
	}

	return 0;
}

bool UDPManager::BindMcast(char *pMcast, unsigned short usPort){
	if(!Bind(usPort)){
		//FIXME do logger
		return false;
	}

	//join multicast group
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(pMcast);
	mreq.imr_interface.s_addr = INADDR_ANY;

	if(setsockopt(m_hSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char FAR*) &mreq, sizeof(mreq)) == SOCKET_ERROR){
		//fixme do logger
		return false;
	}

	return true;
}

int  UDPManager::Send(const char* pBuff, const int iSize){
	if(m_hSocket == INVALID_SOCKET){
		return SOCKET_ERROR;
	}

	int ret = sendto(m_hSocket, (char*)pBuff, iSize, 0, (sockaddr*)&saClient, sizeof(sockaddr));

	if(ret == -1){
		//FIXME do something
	}

	return ret;
}

//all data will be sent guaranteed.
int  UDPManager::SendAll(const char* pBuff, const int iSize){
	if(m_hSocket == INVALID_SOCKET){
		return SOCKET_ERROR;
	}

	if(m_dwTimeoutSend != NO_TIMEOUT){


	}
}

int  UDPManager::Receive(char* pBuff, const int iSize){

}

void UDPManager::SetTimeoutSend(int timeoutInSeconds){

}

void UDPManager::SetTimeoutReceive(int timeoutInSeconds){

}

int  UDPManager::GetTimeoutSend(){

}

int  UDPManager::GetTimeoutReceive(){

}

bool UDPManager::GetRemoteAddr(char* address){

}

bool UDPManager::SetReceiveBufferSize(int sizeInByte){

}

bool UDPManager::SetSendBufferSize(int sizeInByte){

}

int  UDPManager::GetReceiveBufferSize(){

}

int  UDPManager::GetSendBufferSize(){

}

bool UDPManager::SetReuseAddress(bool allowReuse){

}

bool UDPManager::SetEnableBroadcast(bool enableBroadcast){

}

bool UDPManager::SetNonBlocking(bool useNonBlocking){

}

int  UDPManager::GetMaxMsgSize(){

}

/// returns -1 on failure
int  UDPManager::GetTTL(){

	int nTTL;

	if(m_hSocket == INVALID_SOCKET){
		return false;
	}

	#ifndef TARGET_WIN32
		socklen_t nSize = sizeof(int);
	#else
		int nSize = sizeof(int);
	#endif

	if(getsockopt(m_hSocket, IPPROTO_IP, IP_MULTICAST_TTL, (char FAR*) &nTTL, &nSize) == SOCKET_ERROR){
		//FIXME give some error log
		return false;
	}

	return nTTL;
}

bool UDPManager::SetTTL(int nTTL){
	if(m_hSocket == INVALID_SOCKET){
		return false;
	}

	//set time to live of the multicast
	if(setsockopt(m_hSocket, IPPROTO_IP, IP_MULTICAST_TTL, (char FAR*)&nTTL, sizeof(int) == SOCKET_ERROR)){
		//FIXME print warning setsockopt failed
		return false;
	}

	return true;
}


