#pragma once

class MessageEventArgs;

class INetMessageObserver
{
public:
	virtual ~INetMessageObserver(void);

	virtual bool OnReceiveMessage(const MessageEventArgs& message) = 0;
};
