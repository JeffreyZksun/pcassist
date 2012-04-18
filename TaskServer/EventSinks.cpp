#include "stdafx.h"
#include "EventSinks.h"
#include "NotificationMgr.h"
#include "IConnectionPoint.h"
#include "TaskManager.h"

#include "ITaskSystem.h"
#include "MessageResource.h"

RemoteMessageSink::RemoteMessageSink(ITaskSystem* pTaskSystem, TextCommandParser* pCmdLinePaser): m_pTaskSystem(pTaskSystem), m_pCmdLinePaser(pCmdLinePaser)
{
	NotificationMgr::Get()->Subscribe(NetworkEventSource::Get(), this, &m_Filter);
}

RemoteMessageSink::~RemoteMessageSink()
{
	NotificationMgr::Get()->Unsubscribe(NetworkEventSource::Get(), this);
}

void RemoteMessageSink::OnMessageReceived(NetworkMessageEvent* pEvent)
{
	if(NULL == pEvent)
		return;

	WString taskData = pEvent->GetMessage();

	LogOut(taskData);

	if(IConnectionPointPtr pCP = pEvent->GetConnectionPoint())
	{
		pCP->Send(_T("Task is scheduled\r\n"));
	}
}

ConnectionMonitorSink::ConnectionMonitorSink()
{
	NotificationMgr::Get()->Subscribe(NetworkEventSource::Get(), this, &m_Filter);
}
ConnectionMonitorSink::~ConnectionMonitorSink()
{
	NotificationMgr::Get()->Unsubscribe(NetworkEventSource::Get(), this);
}

void ConnectionMonitorSink::OnConnected(NetworkConnectionEvent* pEvent)
{
	if(NULL == pEvent)
		return;

	if(IConnectionPointPtr pCP = pEvent->GetConnectionPoint())
	{
		LogOut(_T("New client connected.\n"));
		pCP->Send(MessageResource::GetWelcomeMesage());
		pCP->Send(MessageResource::GetTaskPromptMesage());
	}
}

void ConnectionMonitorSink::OnDisconnected(NetworkConnectionEvent* pEvent)
{
	LogOut(_T("Client disconnected.\n"));
}
