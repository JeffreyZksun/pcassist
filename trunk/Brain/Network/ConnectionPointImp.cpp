#include "stdafx.h"
/************************************************************************/
// This implementation is based on Boost::asio.
// http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio.html
//
/************************************************************************/
#include "ConnectionPointImp.h"
#include "ConnectionPoint.h"
#include "NotificationMgr.h"
#include "NetworkMessageEvent.h"

#include <iostream>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

// Max message frame size is 1 M.
#define MAX_MESSAGEFRAME_SIZE 2e20

using namespace Ts;


ConnectionPointImp::ConnectionPointImp(ConnectionPoint* pSelf)
    : m_pSelf(pSelf), m_io_service(), m_socket(m_io_service), m_IsConnected(false), m_pReceiveThread(NULL)
{

}

ConnectionPointImp::~ConnectionPointImp()
{
    Close();
}

ConnectionPoint* ConnectionPointImp::Self() const
{
    return m_pSelf;
}

bool ConnectionPointImp::Accept(unsigned short serverPort)
{
    try
    {
        tcp::acceptor acceptor(m_io_service, tcp::endpoint(tcp::v4(), serverPort));

        // ToDo - verify the port issue

        acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor.listen();

        acceptor.accept(m_socket);
        m_IsConnected = true;

        return IsConnected();
    }
    catch (std::exception& e)
    {
        // ToDo - Log it
        std::cerr << e.what() << std::endl;
    }

    return false;
}

bool ConnectionPointImp::ConnectToServer(const WString& serverIP, unsigned short serverPort)
{
    const std::string theServerIP(serverIP.begin(), serverIP.end());

    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(theServerIP), serverPort);
        m_socket.connect(endpoint);
        m_IsConnected = true;

        return IsConnected();
    }
    catch (std::exception& e)
    {
        // ToDo - Log it
        std::cerr << e.what() << std::endl;
    }

    return IsConnected();
}

std::size_t ConnectionPointImp::Send(const WString& strData)
{
    if(!IsConnected())
        return 0;
    
    try
    {
        // Send the wide chars.
        boost::system::error_code error;
        const std::size_t byteSize = boost::asio::write(m_socket, boost::asio::buffer(strData), error);

        if (error)
            m_IsConnected = false;

        // Remarks: The send operation may not transmit all of the data to the peer. 
        // Consider using the write function if you need to ensure that all data is written before the blocking operation completes. 
        // const std::size_t actualSize = m_socket.send(boost::asio::buffer(strData));
        const std::size_t wcharSize = sizeof(wchar_t);
        const std::size_t actualSize = byteSize / wcharSize;

        return actualSize;
    }
    catch (std::exception&)
    {
        // EXCEPTION: The exception is thrown when the remote connection is close. This is acceptable.
        //std::cerr << e.what() << std::endl;
        m_IsConnected = false;
    }

    return 0;
}

bool ConnectionPointImp::Receive(WString& strData)
{
    if(!IsConnected())
        return false;

    strData.clear();
    const std::size_t wcharSize = sizeof(wchar_t);

    for (;;)
    {
        boost::array<wchar_t, 128> buf = {0};
        boost::system::error_code error;

        // boost::asio::read and basic_stream_socket::receive will block until one or more bytes of data has been received successfully,
        // or until an error occurs. 
        // In our design, during a TCP connection session, we will process many bidirectional transfer. And will keep the connection alive.
        // What we want is 1. when there is no data received, block the function. 2. If there is any data, even though there is only one byte,
        // return the data directly.
        //const std::size_t byteSize = boost::asio::read(m_socket, boost::asio::buffer(buf), error);
        const std::size_t byteSize = m_socket.read_some(boost::asio::buffer(buf), error);//boost::asio::read(m_socket, boost::asio::buffer(buf), error);

        const std::size_t actualSize = byteSize / wcharSize;
        if(actualSize > 0)
            strData.append(buf.data(), actualSize);

        if (error)
        {
            m_IsConnected = false;
            break; 
        }

        // Check the cache size to avoid the exhaustion of the memory.
        if(strData.size() > MAX_MESSAGEFRAME_SIZE)
            break;

        if(m_socket.available() == 0) // No more data in the socket buffer
            break;
    }

    return strData.size() > 0;
}

void ConnectionPointImp::Receive_Asyc()
{
    m_pReceiveThread = new boost::thread(boost::bind( &ConnectionPointImp::_Receive_Asyc, this ));
}

void ConnectionPointImp::_Receive_Asyc()
{
    while(IsConnected())
    {
        WString strData;
        
        if(Receive(strData))
        {
            NetworkMessageEvent nwEvent(this->Self(), strData);
            NotificationMgr::Get()->Fire(&nwEvent);
        }
    }
}

WString ConnectionPointImp::GetRemoteIP()
{
    if(!IsConnected())
        return WString();

    unsigned short lp = m_socket.local_endpoint().port();
    unsigned short rp = m_socket.remote_endpoint().port();

    std::string addr = m_socket.remote_endpoint().address().to_string();

    WString waddr(addr.begin(), addr.end());
    return waddr;
}

bool ConnectionPointImp::Close()
{
    if(IsConnected())
    {
        // Remarks
        // For portable behavior with respect to graceful closure of a connected socket, 
        // call shutdown() before closing the socket. 

        boost::system::error_code error;
        m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
        m_socket.close(error);
        m_IsConnected = false;
    }

    if(m_pReceiveThread != NULL)
    {
        // ToDo - Do we need to kill the thread?
        delete m_pReceiveThread;
        m_pReceiveThread = NULL;
    }

    return !IsConnected();
}

bool ConnectionPointImp::IsConnected() const
{
    // Due to the limitation of the underlying socket interface, there is no way to implement the function like isConnected to check the TCP connection status at the socket level. 
    // In our implementation, we cache a connection status flag (bool m_IsConnected). It assumes that if there is no error from socket, the TCP connection is alive.
    // The flag will be updated every time when use the socket. If there are errors when send and read data, that means the connection is disconnected.
    // Then change the flag correspondingly. If the TCP connection is idle for a long time. This flag doesn't reflect the actual status of the TCP connection until using the socket.
    // For example, the socket is idle for a long time. It is disconnected due to the poor network. In this case, the m_IsConnected is still true since we don't 
    // get any callback regarding the disconnection event. When try to send data through this socket, there will be error. And now we know that the connection is disconnected.
    // http://stackoverflow.com/questions/9920370/how-to-check-if-a-socket-connection-is-live-in-boostasio
    // http://stackoverflow.com/questions/1511129/boostasioiptcpsocket-is-connected

    return m_IsConnected;
}

