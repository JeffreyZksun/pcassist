#include "stdafx.h"

#include "TCPServerImp.h"
#include "ConnectionPoint.h"
#include "ConnectionPointImp.h"

using namespace Ts;


TCPServerImp::TCPServerImp(TCPServerBackPtr pSelf, unsigned short serverPort) : m_pSelf(pSelf), m_ConnectionGroup(), m_ServerPort(serverPort)
    , m_acceptor(m_ConnectionGroup.io_service(), tcp::endpoint(tcp::v4(), serverPort)) , m_pListeningConnectionImp()
{

}

TCPServerImp::~TCPServerImp(void)
{
    Close();
}

TCPServerPtr TCPServerImp::Self() const
{
    return m_pSelf.lock();
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
}

bool TCPServerImp::BroadcastToClients(const WString& message)
{
    m_ConnectionGroup.Send(message);

    return true;
}

void TCPServerImp::start_accept()
{
    m_pListeningConnectionImp.reset(new ConnectionPointImp(m_ConnectionGroup.io_service()));
    m_acceptor.async_accept(m_pListeningConnectionImp->socket(),
        boost::bind(&TCPServerImp::handle_accept, this,
        boost::asio::placeholders::error));
}

void TCPServerImp::handle_accept(const boost::system::error_code& error)
{
    if (!error)
    {
        IConnectionPointPtr pCP = ConnectionPoint::Create(m_pListeningConnectionImp);
        m_ConnectionGroup.Add(pCP);
        m_pListeningConnectionImp->Start();
    }

    start_accept();
}
