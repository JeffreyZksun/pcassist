#include "stdafx.h"

#include "TCPClient.h"
#include "TCPClientImp.h"

using namespace Ts;

TCPClient::TCPClient()
{
    
}

TCPClient::~TCPClient(void)
{

}

TCPClientPtr TCPClient::Create(const WString& serverIP, unsigned short serverPort)
{
    TCPClientPtr pNewObj(new TCPClient());
    pNewObj->m_pImp.reset(new TCPClientImp(pNewObj, serverIP, serverPort));

    return pNewObj;
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
