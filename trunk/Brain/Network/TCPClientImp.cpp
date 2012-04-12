#include "stdafx.h"


#include "TCPClientImp.h"
#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"

using namespace Ts;

TCPClientImp::TCPClientImp(TCPClient* pSelf, const WString& serverIP, unsigned short serverPort) 
    : m_pSelf(pSelf), m_ConnectionGroup(), m_ServerIP(serverIP), m_ServerPort(serverPort)
{
}

TCPClientImp::~TCPClientImp(void)
{
    Close();
}

TCPClient* TCPClientImp::Self() const
{
    return m_pSelf;
}

bool TCPClientImp::ConnectToServer()
{
    IConnectionPointPtr  pConnectionPoint = m_ConnectionGroup.GetConnectionPoint(0);
    if(NULL == pConnectionPoint)
    {
        ConnectionPointImpPtr pImp(new ConnectionPointImp(m_ConnectionGroup.io_service()));
        pConnectionPoint = ConnectionPoint::Create(pImp);

        m_ConnectionGroup.Add(pConnectionPoint);
    }

    bool ok = pConnectionPoint->ConnectToServer(m_ServerIP, m_ServerPort);
    if(ok)
    {
        m_ConnectionGroup.Start();
    }

    return ok;
}

void TCPClientImp::Close()
{
    m_ConnectionGroup.Close();
}

void TCPClientImp::SendToServer(const WString& message)
{
    m_ConnectionGroup.Send(message);
}

bool TCPClientImp::IsConnected() const
{
    IConnectionPointPtr  pConnectionPoint = m_ConnectionGroup.GetConnectionPoint(0);
    if(NULL == pConnectionPoint)
        return false;

    return pConnectionPoint->IsConnected();
}






