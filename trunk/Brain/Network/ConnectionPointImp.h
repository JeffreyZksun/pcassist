/**********************************************************/
// Create TCP connection between two endpoints. The connection keeps alive.
// Due to the TCP protocol, the TCP connection will be closed if there is no data transformation after a specified time duration. (RIght?)
// * To keep the TCP connection alive, the workaround is implement the heartbeat protocol on the top of the connection. (Not implemented yet)

/**********************************************************/

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;

namespace Ts
{
    class ConnectionPoint;


    class ConnectionPointImp
    {
    public:
        ConnectionPointImp(ConnectionPoint* pSelf);

        ~ConnectionPointImp(void);
        ConnectionPoint*    Self() const;

    public:

        bool                Accept(unsigned short serverPort); // work as server
        bool                ConnectToServer(const WString& serverIP, unsigned short serverPort); // work as client
        bool                Close();

        std::size_t         Send(const WString& strData);
        bool                Receive(WString& strData);
        void                Receive_Asyc();

        WString             GetRemoteIP();

        bool                IsConnected() const;

    private:
        void                _Receive_Asyc();

    private:
        ConnectionPoint*                m_pSelf;

        boost::asio::io_service         m_io_service;
        boost::asio::ip::tcp::socket    m_socket;
        bool                            m_IsConnected;
        boost::thread*                  m_pReceiveThread;
    };

}