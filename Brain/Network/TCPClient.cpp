#include "stdafx.h"

#include "TCPClient.h"
#include "TCPClientImp.h"

using namespace Ts;

TCPClient::TCPClient(const WString& serverIP, unsigned short serverPort) : m_pImp(NULL)
{
    m_pImp = new TCPClientImp(this, serverIP, serverPort);
}

TCPClient::~TCPClient(void)
{
    if(m_pImp)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
}

bool TCPClient::ConnectToServer()
{
    return m_pImp->ConnectToServer();
}

void TCPClient::Close()
{
    return m_pImp->Close();
}

void TCPClient::SendToServer(const WString& message)
{
    m_pImp->SendToServer(message);
}

bool TCPClient::IsConnected() const
{
    return m_pImp->IsConnected();
}
