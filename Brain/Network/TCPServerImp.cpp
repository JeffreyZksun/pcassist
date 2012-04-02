#include "stdafx.h"

#include "TCPServerImp.h"
#include "ConnectionPoint.h"

using namespace Ts;


TCPServerImp::TCPServerImp(TCPServer* pSelf, unsigned short serverPort) : m_pSelf(pSelf), m_ClientList(), m_ServerPort(serverPort), m_pListenThread(NULL)
{

}

TCPServerImp::~TCPServerImp(void)
{
    Close();
}

TCPServer* TCPServerImp::Self() const
{
    return m_pSelf;
}

bool TCPServerImp::StartListen_Asyc()
{
    m_pListenThread = new boost::thread(boost::bind( &TCPServerImp::_StartListen_Asyc, this ));

    return true;
}

void TCPServerImp::_StartListen_Asyc()
{
    while(true)
    {
        IConnectionPoint* pCP = new ConnectionPoint();

        // Start to listen the incoming TCP connection request.
        bool bSucc = pCP->Accept(m_ServerPort);
        if(bSucc)
        {
            // ToDo - lock the list
            m_ClientList.push_back(pCP);

            pCP->Receive_Asyc();
        }
        else
        {
            delete pCP;
            pCP = NULL;
        }
    }
}

void TCPServerImp::Close()
{
    // Kill the listening thread first.

    if(m_pListenThread != NULL)
    {
        // ToDo - Do we need to kill the thread?
        delete m_pListenThread;
        m_pListenThread = NULL;
    }

    while (!m_ClientList.empty())
    {
        IConnectionPoint* pCP = m_ClientList.back();
        delete pCP;
        m_ClientList.pop_back();
    }
}

bool TCPServerImp::BroadcastToClients(const WString& message)
{
    for(ConnectionPointList::iterator it = m_ClientList.begin(); it != m_ClientList.end(); ++it)
    {
        (*it)->Send(message);
    }

    return true;
}


