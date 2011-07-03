#include "StdAfx.h"
#include "ConnectionPoint.h"
#include <afxcom_.h> // For ASSERT

// http://www.codeproject.com/KB/IP/beginningtcp_cpp.aspx
// Don't forget link Ws2_32.lib
#define SCK_VERSION1            0x0101
#define SCK_VERSION2            0x0202

// The caller must be responsible for release the returned memory.
char* CStringToChar(const CString& str)
{
	size_t   i;
	const int lenStr = str.GetLength() + 1; // Convert wchar_t to char.
	char* pStrBuffer = new char[lenStr];
	::wcstombs_s(&i, pStrBuffer, lenStr, str, lenStr);

	return pStrBuffer;
}

// Thread Entry - Listen the communication
DWORD WINAPI StartListening(LPVOID pParam)
{
	ConnectionPoint* pSelf = (ConnectionPoint*)pParam;
	if (!pSelf->IsConnected())
		return 1; // Not expected.

	while(1)
	{
		// receive the request from the client	
		const int bufferLength = 128;
		char charMsg[bufferLength];
		memset(charMsg,0,sizeof(charMsg));

		int numBytes = recv(pSelf->GetSocket(),charMsg,bufferLength,0);
		if (numBytes > 0)
		{
			// ToDo - dispatch the message.
			numBytes = numBytes;
		}
	}

	return 0;
}

ConnectionPoint::ConnectionPoint(void)
	: mSocket(INVALID_SOCKET), mCommunicationThreadHandle(INVALID_HANDLE_VALUE)
{
}

ConnectionPoint::~ConnectionPoint(void)
{
}

bool ConnectionPoint::ConnectToServer(unsigned short serverPort, CString serverIP)
{
	ASSERT(!IsConnected());
	if(IsConnected())
		return false;

	// Initialize the socket 
	mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(mSocket == INVALID_SOCKET)
		return false; // Failed to create the socket.

	// Connect to the remote server
	SOCKADDR_IN serverInfo; // Socket Address Information
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(serverPort);

	char* pStr = CStringToChar(serverIP);
	serverInfo.sin_addr.s_addr = inet_addr(pStr);
	delete[] pStr;

	if (::connect(mSocket, (SOCKADDR *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		return false; //Couldn't connect
	}

	// Start listening
	_StartListening();

	return true; //Success
}

bool ConnectionPoint::Attach(SOCKET remoteSocket, const SOCKADDR_IN& remoteAddrInfo)
{
	mSocket = remoteSocket;
	// ToDo - save the remote info

	// Start listening
	_StartListening();

	return true; //Success
}

bool ConnectionPoint::Send(const CString& strData)
{
	if(!IsConnected())
		return false;

	char* pStr = CStringToChar(strData);
	int length = strlen(pStr);
	int error = ::send(mSocket, pStr, length, 0);

	return error != SOCKET_ERROR;

}

bool ConnectionPoint::IsConnected()
{
	return mSocket != INVALID_SOCKET;
}

SOCKET ConnectionPoint::GetSocket()
{
	return mSocket;
}

bool ConnectionPoint::StartupWinSocket()
{
	// Start up win socket. Use version 2
	WSADATA wsadata;
	int error = ::WSAStartup(SCK_VERSION2, &wsadata);
	if(error)
		return false;

	if(wsadata.wVersion != SCK_VERSION2)
	{
		::WSACleanup();
		return false;
	}

	return true;
}
void ConnectionPoint::CleanupWinSocket()
{
	::WSACleanup();
}

void ConnectionPoint::_StartListening()
{
	if(!IsConnected())
		return;

	mCommunicationThreadHandle = ::CreateThread(0, 0, StartListening, (LPVOID)this, 0, 0);
}

// This function will be bloc until an new client is connected.
bool ConnectionPoint::Accept(unsigned short serverPort, int maxConnectionCount
							 , SOCKET& remoteSocket, SOCKADDR_IN& remoteAddrInfo)
{
	if(!IsConnected())
	{
		mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(mSocket == INVALID_SOCKET)
			return false; // Failed to create the socket.

		// Bind the port and listening
		SOCKADDR_IN serverInfo; // Socket Address Information
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(serverPort);
		serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);

		if (::bind(mSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
		{
			//We couldn't bind (this will happen if you try to bind to the same  
			//socket more than once)

			return false;
		}

		::listen(mSocket, maxConnectionCount);
	}

	// Block and accept the request.
	remoteSocket = INVALID_SOCKET;
	int clientInfoLength = sizeof(remoteAddrInfo);
	// The function will not return until a connection request is made.
	// Accepts a new client connection and stores its socket file descriptor
	if ((remoteSocket = ::accept(mSocket, (LPSOCKADDR)&remoteAddrInfo, &clientInfoLength)) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}
