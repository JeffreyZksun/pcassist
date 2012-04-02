#include "stdafx.h"


#include "TCPClientImp.h"
#include "ConnectionPoint.h"

using namespace Ts;

TCPClientImp::TCPClientImp(TCPClient* pSelf, const WString& serverIP, unsigned short serverPort) 
    : m_pSelf(pSelf), m_pConnectionPoint(NULL), m_ServerIP(serverIP), m_ServerPort(serverPort)
{
}

TCPClientImp::~TCPClientImp(void)
{
    if(m_pConnectionPoint != NULL)
    {
        delete m_pConnectionPoint;
        m_pConnectionPoint = NULL;
    }


}

TCPClient* TCPClientImp::Self() const
{
    return m_pSelf;
}

bool TCPClientImp::ConnectToServer()
{
    if(NULL == m_pConnectionPoint)
    {
        m_pConnectionPoint = new ConnectionPoint();
    }

    bool ret = m_pConnectionPoint->ConnectToServer(m_ServerIP, m_ServerPort);
    if(ret)
        m_pConnectionPoint->Receive_Asyc();

    return ret;
}

void TCPClientImp::Close()
{
    if(m_pConnectionPoint != NULL)
    {
        delete m_pConnectionPoint;
        m_pConnectionPoint = NULL;
    }
}

std::size_t TCPClientImp::SendToServer(const WString& message)
{
    if(NULL == m_pConnectionPoint)
        return false;

    return m_pConnectionPoint->Send(message);
}

bool TCPClientImp::IsConnected() const
{
    if(NULL == m_pConnectionPoint)
        return false;

    return m_pConnectionPoint->IsConnected();
}






