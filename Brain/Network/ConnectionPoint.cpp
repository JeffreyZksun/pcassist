#include "stdafx.h"


#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"

using namespace Ts;

ConnectionPoint::ConnectionPoint(ConnectionPointImp* pImp)
    : m_pImp(pImp)
{
    if(m_pImp != NULL)
        m_pImp->SetSelf(this);
}

ConnectionPoint::~ConnectionPoint()
{
    if(m_pImp)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
}

bool ConnectionPoint::ConnectToServer(const WString& serverIP, unsigned short serverPort)
{
    return m_pImp->ConnectToServer(serverIP, serverPort);
}

void ConnectionPoint::Close()
{
    m_pImp->Close();
}

void ConnectionPoint::Send(const WString& strData)
{
    m_pImp->Send(strData);
}

WString ConnectionPoint::GetRemoteIP() const
{
    return m_pImp->GetRemoteIP();
}

unsigned short ConnectionPoint::GetRemotePort() const
{
    return m_pImp->GetRemotePort();
}

unsigned short ConnectionPoint::GetLocalPort() const
{
    return m_pImp->GetLocalPort();
}

bool ConnectionPoint::IsConnected() const
{
    return m_pImp->IsConnected();
}

