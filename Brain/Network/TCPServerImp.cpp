#include "stdafx.h"

#include "TCPServerImp.h"
#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"

using namespace Ts;


TCPServerImp::TCPServerImp(TCPServer* pSelf, unsigned short serverPort) : m_pSelf(pSelf), m_ConnectionGroup(), m_ServerPort(serverPort)
    , m_acceptor(m_ConnectionGroup.io_service(), tcp::endpoint(tcp::v4(), serverPort)) , m_pListeningConnectionImp(NULL)
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


bool TCPServerImp::Start()
{
    start_accept();

    m_ConnectionGroup.Start();

    return true;
}


void TCPServerImp::Close()
{
    m_acceptor.close();

    m_ConnectionGroup.Close();

    if(m_pListeningConnectionImp)
    {
        delete m_pListeningConnectionImp;
        m_pListeningConnectionImp = NULL;
    }
}

bool TCPServerImp::BroadcastToClients(const WString& message)
{
    m_ConnectionGroup.Send(message);

    return true;
}

void TCPServerImp::start_accept()
{
    m_pListeningConnectionImp = new ConnectionPointImp(m_ConnectionGroup.io_service());
    m_acceptor.async_accept(m_pListeningConnectionImp->socket(),
        boost::bind(&TCPServerImp::handle_accept, this, m_pListeningConnectionImp,
        boost::asio::placeholders::error));
}

void TCPServerImp::handle_accept(ConnectionPointImp* pImp,
    const boost::system::error_code& error)
{
    if (!error)
    {
        IConnectionPoint* pCP = new ConnectionPoint(pImp);
        m_ConnectionGroup.Add(pCP);
        pImp->Start();
    }

    start_accept();
}
