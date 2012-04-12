#include "stdafx.h"
/************************************************************************/
// This implementation is based on Boost::asio.
// http://www.boost.org/doc/libs/1_49_0/doc/html/boost_asio.html
//
/************************************************************************/
#include "ConnectionPointImp.h"
#include "ConnectionPoint.h"
#include "NotificationMgr.h"
#include "NetworkEvents.h"
#include "ThreadLocks.h"

#include <iostream>
#include <boost/array.hpp>

#include <codecvt>

#include <cstdio>
#include <cstdlib>
#include <cstring>


using boost::asio::ip::tcp;

using namespace Ts;

#define  MAX_MESSAGEQUE_LENGTH 10

/************************************************************************/
/*                                                                      */
/************************************************************************/
// http://stackoverflow.com/questions/6140223/c-boost-encode-decode-utf-8
inline void decode_utf8(const std::string& bytes, std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    wstr = conv.from_bytes(bytes);
}
inline void encode_utf8(const std::wstring& wstr, std::string& bytes)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    bytes = conv.to_bytes(wstr);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

ConnectionPointImp::ConnectionPointImp(ConnectionPointBackPtr pSelf, boost::asio::io_service& io_service)
    : m_pSelf(pSelf),  m_socket(io_service), m_IsConnected(false)
{

}

ConnectionPointImp::ConnectionPointImp( boost::asio::io_service& io_service)
    : m_pSelf(),  m_socket(io_service), m_IsConnected(false)
{

}

ConnectionPointImp::~ConnectionPointImp()
{
    Close();
}

ConnectionPointPtr ConnectionPointImp::Self() const
{
    return m_pSelf.lock();
}

void ConnectionPointImp::SetSelf(ConnectionPointBackPtr pSelf)
{
    m_pSelf = pSelf;
}

bool ConnectionPointImp::ConnectToServer(const WString& serverIP, unsigned short serverPort)
{
    const std::string theServerIP(serverIP.begin(), serverIP.end());

    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(theServerIP), serverPort);
        m_socket.connect(endpoint);

        Start();

        return IsConnected();
    }
    catch (std::exception& e)
    {
        // ToDo - Log it
        std::cerr << e.what() << std::endl;
    }

    return IsConnected();
}

WString ConnectionPointImp::GetRemoteIP() const
{
    if(!IsConnected())
        return WString();

    unsigned short lp = m_socket.local_endpoint().port();
    unsigned short rp = m_socket.remote_endpoint().port();

    std::string addr = m_socket.remote_endpoint().address().to_string();

    WString waddr(addr.begin(), addr.end());
    return waddr;
}

unsigned short ConnectionPointImp::GetRemotePort() const
{
    if(!IsConnected())
        return 0;

    return m_socket.remote_endpoint().port();
}

unsigned short ConnectionPointImp::GetLocalPort() const
{
    if(!IsConnected())
        return 0;

    return m_socket.local_endpoint().port();
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

tcp::socket& ConnectionPointImp::socket()
{
    return m_socket;
}

void ConnectionPointImp::Start()
{
    m_IsConnected = true;

    do_async_read();
}


void ConnectionPointImp::Send(const WString& msg)
{
    if(!IsConnected())
        return;
    RECURSIVE_LOCK_GUARD(m_mutexWriteMessageQueue);

    if(m_WriteMessageQueue.size() > MAX_MESSAGEQUE_LENGTH)
        return;

    bool write_in_progress = !m_WriteMessageQueue.empty();
    m_WriteMessageQueue.push_back(msg);
    if (!write_in_progress)
    {
        do_async_write();
    }
}

void ConnectionPointImp::Close()
{
    bool bPreviousConnected = IsConnected();
    if(bPreviousConnected)
    {
        m_IsConnected = false;

        boost::system::error_code ec;
        m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ec);
        m_socket.close(ec);
    }

    if(this->Self() != NULL)
    {
        NetworkConnectionEvent nwEvent(this->Self(), NetworkConnectionEvent::eDisconnect);
        NotificationMgr::Get()->Fire(&nwEvent);
    }
}

void ConnectionPointImp::handle_read_line(const boost::system::error_code& error)
{
    if (!error)
    {
        if(this->Self() != NULL)
        {

            std::istream response_stream(&m_ReceivedBuffer);
            std::string strLine;

            // The receive buffer may contains multiple lines of data. We need to split it and remove the suffix.
            while (std::getline(response_stream, strLine, '\n'))
            {
                //strLine.pop_back(); // The '\n' is NOT returned. Do NOT need to pop it.
                // strLine.pop_back(); // '\r'
                strLine.push_back('\n'); // The '\n' is NOT returned. Append it. 

                WString strData;
                decode_utf8(strLine, strData);

                NetworkMessageEvent nwEvent(this->Self()->shared_from_this(), strData);
                NotificationMgr::Get()->Fire(&nwEvent);
            }
        }

        do_async_read();
    }
    else
    {
        Close();
    }
}

void ConnectionPointImp::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        RECURSIVE_LOCK_GUARD(m_mutexWriteMessageQueue);

        m_WriteMessageQueue.pop_front();
        if (!m_WriteMessageQueue.empty())
        {
            do_async_write();
        }
    }
    else
    {
        Close();
    }
}

void ConnectionPointImp::do_async_write()
{
    if(!IsConnected())
        return;
    {
        if(m_WriteMessageQueue.empty())
            return;

        encode_utf8(m_WriteMessageQueue.front(), m_WrittingBuffer);
    }

    //m_WrittingBuffer.push_back('\r');
    //m_WrittingBuffer.push_back('\n');

    boost::asio::async_write(m_socket,
        boost::asio::buffer(m_WrittingBuffer.data(),
        m_WrittingBuffer.length()),
        boost::bind(&ConnectionPointImp::handle_write, this,
        boost::asio::placeholders::error));
}

void ConnectionPointImp:: do_async_read()
{
    if(!IsConnected())
        return;

    boost::asio::async_read_until(m_socket, m_ReceivedBuffer, "\r\n",
        boost::bind(&ConnectionPointImp::handle_read_line, this,
        boost::asio::placeholders::error));

    // Clear the buffer.
    m_ReceivedBuffer.consume(m_ReceivedBuffer.size());
}