#include "stdafx.h"

#include "TCPServer.h"
#include "TCPServerImp.h"

using namespace Ts;

TCPServer::TCPServer() : m_pImp()
{
}

TCPServer::~TCPServer(void)
{
}

TCPServerPtr TCPServer::Create(unsigned short serverPort)
{
    TCPServerPtr pNewObj(new TCPServer());
    pNewObj->m_pImp.reset(new TCPServerImp(pNewObj, serverPort));

    return pNewObj;
}

bool TCPServer::Start()
{
    return m_pImp->Start();
}

void TCPServer::Close()
{
    m_pImp->Close();
}
bool TCPServer::BroadcastToClients(const WString& message)
{
    return m_pImp->BroadcastToClients(message);
}


