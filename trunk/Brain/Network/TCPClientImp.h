#pragma once

namespace Ts
{
    class IConnectionPoint;
    class TCPClient;


    class TCPClientImp
    {
    public:
        TCPClientImp(TCPClient* pSelf, const WString& serverIP, unsigned short serverPort);
        ~TCPClientImp(void);

        TCPClient*    Self() const;

    public:

        bool                    ConnectToServer();
        virtual void            Close();
        std::size_t             SendToServer(const WString& message);

        bool                    IsConnected() const;

    private:
        TCPClient*          m_pSelf;

        IConnectionPoint*   m_pConnectionPoint;
        WString             m_ServerIP;
        unsigned short      m_ServerPort;

    };
}