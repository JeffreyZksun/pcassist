#pragma once

class INetMessageObserver;

class ConnectionPoint
{
public:
	ConnectionPoint(void);
	~ConnectionPoint(void);

public:
	bool	Accept(unsigned short serverPort, int maxConnectionCount
				, SOCKET& remoteSocket, SOCKADDR_IN& remoteAddrInfo);

	bool	ConnectToServer(unsigned short serverPort, CString strIP);
	bool	Attach(SOCKET remoteSocket, const SOCKADDR_IN& remoteAddrInfo);

	bool	Send(const CString& strData);

	bool	IsConnected();

	SOCKET	GetSocket();

public:
	static bool	StartupWinSocket();
	static void	CleanupWinSocket();

private:
	void	_StartListening();

private:
	SOCKET		mSocket;
	HANDLE		mCommunicationThreadHandle;
};
