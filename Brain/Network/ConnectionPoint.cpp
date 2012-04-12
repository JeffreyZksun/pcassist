#include "stdafx.h"


#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"
#include "ThreadLocks.h"

using namespace Ts;

ConnectionPoint::ConnectionPoint()
{

}

ConnectionPoint::~ConnectionPoint()
{
    // Do nothing to m_pImp
}

ConnectionPointPtr ConnectionPoint::Create(ConnectionPointImpPtr pImp)
{
    ConnectionPointPtr pNewObj(new ConnectionPoint());
    pNewObj->m_pImp = pImp;
    if(pImp)
        pImp->SetSelf(pNewObj);

    return pNewObj;
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

