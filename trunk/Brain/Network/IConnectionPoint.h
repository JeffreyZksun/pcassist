#pragma once
/*****************************************************************************/
// *********************REMARK*********************
// When define the application framework, don't use any library-related type,
// even though it is accepted by standard.
// Use the language grammar only. 
// When change the dependent libraries someday, We can benefit from this rule.
/*****************************************************************************/
namespace Ts
{
    class IConnectionPoint
    {
    public:
        virtual ~IConnectionPoint(void){};

        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort) = 0;
        virtual void                Close() = 0;

        virtual void                Send(const WString& strData) = 0;

        virtual WString             GetRemoteIP() const = 0;
        virtual unsigned short      GetRemotePort() const = 0;
        virtual unsigned short      GetLocalPort() const = 0;
        virtual bool                IsConnected() const = 0;
    };
}
