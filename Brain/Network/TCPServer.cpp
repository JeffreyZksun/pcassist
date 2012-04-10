#include "stdafx.h"

#include "TCPServer.h"
#include "TCPServerImp.h"

using namespace Ts;

TCPServer::TCPServer(unsigned short serverPort) : m_pImp(NULL)
{
    m_pImp = new TCPServerImp(this, serverPort);
}

TCPServer::~TCPServer(void)
{
    if(m_pImp)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
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


