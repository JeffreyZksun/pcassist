/**********************************************************/
// Create TCP connection between two endpoints. The connection keeps alive.
// Due to the TCP protocol, the TCP connection will be closed if there is no data transformation after a specified time duration. (RIght?)
// * To keep the TCP connection alive, the workaround is implement the heartbeat protocol on the top of the connection. (Not implemented yet)

/**********************************************************/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

using namespace boost::asio;
using boost::asio::ip::tcp;

namespace Ts
{
    class ConnectionPoint;

    class ConnectionPointImp 
    {
    public:
        ConnectionPointImp(ConnectionPoint* pSelf, boost::asio::io_service& io_service);
        ConnectionPointImp(boost::asio::io_service& io_service);

        ~ConnectionPointImp(void);
        ConnectionPoint*    Self() const;
        void                SetSelf( ConnectionPoint* pSelf);

    public:
        bool                ConnectToServer(const WString& serverIP, unsigned short serverPort);
        void                Start();
        void                Close();

        void                Send(const WString& strData);


        WString             GetRemoteIP() const;
        unsigned short      GetRemotePort() const;
        unsigned short      GetLocalPort() const;
        bool                IsConnected() const;

    private:


        ////////////////////////////New impl///////////
    public:
        tcp::socket&        socket();

    private:
        void                do_async_write();
        void                do_async_read();

        void                handle_read_line(const boost::system::error_code& error);
        void                handle_write(const boost::system::error_code& error);
        
    private:
        typedef std::deque<WString>     MessageQueue;

    private:
        ConnectionPoint*                m_pSelf;

        boost::asio::ip::tcp::socket    m_socket;

        // Thread Safety: lock this mutex before accessing m_WriteMessageQueue
        // Lock this mutex recursively in the same thread.
        mutable boost::recursive_mutex  m_mutexWriteMessageQueue; 
        MessageQueue                    m_WriteMessageQueue;
        boost::asio::streambuf          m_ReceivedBuffer;
        std::string                     m_WrittingBuffer;

        bool                            m_IsConnected;

    };

}