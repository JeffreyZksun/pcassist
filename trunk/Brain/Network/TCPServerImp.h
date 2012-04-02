#pragma once

#include <list>
#include <boost/thread.hpp>

namespace Ts
{
    class IConnectionPoint;
    class TCPServer;


    class TCPServerImp
    {
    public:
        TCPServerImp(TCPServer* pSelf, unsigned short serverPort);
        ~TCPServerImp(void);

        TCPServer*      Self() const;

    public:

        bool            StartListen_Asyc();
        void            Close();
        bool            BroadcastToClients(const WString& message);


    private:
         void           _StartListen_Asyc();

    private:
        typedef std::list<IConnectionPoint*> ConnectionPointList;

    private:
        TCPServer*              m_pSelf;

        ConnectionPointList     m_ClientList;
        unsigned short          m_ServerPort;

        boost::thread*          m_pListenThread;

    };
}