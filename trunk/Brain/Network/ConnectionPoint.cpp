#include "stdafx.h"


#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"

using namespace Ts;

ConnectionPoint::ConnectionPoint()
    : m_pImp(NULL)
{
    m_pImp = new ConnectionPointImp(this);
}

ConnectionPoint::~ConnectionPoint()
{
    if(m_pImp)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
}

bool ConnectionPoint::Accept(unsigned short serverPort)
{
    return m_pImp->Accept(serverPort);
}

bool ConnectionPoint::ConnectToServer(const WString& serverIP, unsigned short serverPort)
{
    return m_pImp->ConnectToServer(serverIP, serverPort);
}

std::size_t ConnectionPoint::Send(const WString& strData)
{
    return m_pImp->Send(strData);
}

bool ConnectionPoint::Receive(WString& strData)
{
    return m_pImp->Receive(strData);
}

void ConnectionPoint::Receive_Asyc()
{
    m_pImp->Receive_Asyc();
}

WString ConnectionPoint::GetRemoteIP()
{
    return m_pImp->GetRemoteIP();
}

bool ConnectionPoint::Close()
{
    return m_pImp->Close();
}

bool ConnectionPoint::IsConnected() const
{
    return m_pImp->IsConnected();
}

