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

}

bool UDPManager::Connect(const char *pHost, unsigned short usPort){

}

bool UDPManager::ConnectMcast(char *pMcast, unsigned short usPort){

}

bool UDPManager::Bind(unsigned short usPort){

}

bool UDPManager::BindMcast(char *pMcast, unsigned short usPort){

}

int  UDPManager::Send(const char* pBuff, const int iSize){

}

//all data will be sent guaranteed.
int  UDPManager::SendAll(const char* pBuff, const int iSize){

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

}

bool UDPManager::SetTTL(int nTTL){

}


