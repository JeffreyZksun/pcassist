/**********************************************************/
// Create TCP connection between two endpoints. The connection keeps alive.
// Due to the TCP protocol, the TCP connection will be closed if there is no data transformation after a specified time duration. (RIght?)
// * To keep the TCP connection alive, the workaround is implement the heartbeat protocol on the top of the connection. (Not implemented yet)

/**********************************************************/

#pragma once

#include <boost/asio.hpp>
#include <boost/weak_ptr.hpp>
#include <deque>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using boost::asio::ip::tcp;

namespace Ts
{
    class ConnectionPoint;

    typedef boost::weak_ptr<ConnectionPoint>    ConnectionPointBackPtr;
    typedef boost::shared_ptr<ConnectionPoint>  ConnectionPointPtr;

    class ConnectionPointImp : public boost::enable_shared_from_this<ConnectionPointImp>
    {
    public:
        ConnectionPointImp(ConnectionPointBackPtr pSelf, boost::asio::io_service& io_service);
        ConnectionPointImp(boost::asio::io_service& io_service);

        ~ConnectionPointImp(void);
        ConnectionPointPtr  Self() const;
        void                SetSelf(ConnectionPointBackPtr pSelf);

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
        ConnectionPointBackPtr          m_pSelf;

        boost::asio::ip::tcp::socket    m_socket;

        MessageQueue                    m_WriteMessageQueue;
        boost::asio::streambuf          m_ReceivedBuffer;
        std::string                     m_WrittingBuffer;

        bool                            m_IsConnected;

    };

}