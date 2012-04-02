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

        virtual bool                Accept(unsigned short serverPort) = 0; // work as server
        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort) = 0; // work as client
        virtual bool                Close() = 0;

        virtual std::size_t         Send(const WString& strData) = 0;
        virtual bool                Receive(WString& strData) = 0;
        virtual void                Receive_Asyc() = 0;

        virtual WString             GetRemoteIP() = 0;

        virtual bool                IsConnected() const = 0;
    };
}
