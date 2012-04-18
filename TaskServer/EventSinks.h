#pragma once

#include <NetworkEvents.h>
#include "EventFilters.h"

class ITaskSystem;

class RemoteMessageSink: public NetworkMessageEventSink
{
public:
	RemoteMessageSink(ITaskSystem* pTaskSystem);
	~RemoteMessageSink();

	virtual void OnMessageReceived(NetworkMessageEvent* pEvent);

private:
	ITaskSystem*	m_pTaskSystem;
	NetworkMessageEventFilter m_Filter;
};

class ConnectionMonitorSink : public NetworkConnectionEventSink
{
public:
	ConnectionMonitorSink();
	~ConnectionMonitorSink();

public:
	virtual void OnConnected(NetworkConnectionEvent* pEvent);
	virtual void OnDisconnected(NetworkConnectionEvent* pEvent);

private:
	DefaultFilter                   m_Filter;
};