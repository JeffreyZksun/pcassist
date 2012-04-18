#include "stdafx.h"
#include "EventSinks.h"
#include "NotificationMgr.h"
#include "IConnectionPoint.h"
#include "TaskManager.h"
#include "TextCommandParser.h"
#include "CmdLineMgr.h"

#include "ITaskSystem.h"
#include "MessageResource.h"

bool IsCandidateCommandOptions(const WString& message)
{
	size_t pos = message.find(L'-');
	return pos != -1;
}

void SendDescription(IConnectionPointPtr pCP, Ts::CmdLineMgr::pointer pCmdLineMgr)
{
	if(!pCP || !pCmdLineMgr)
		return;

	const NString options_Desc = pCmdLineMgr->GetOptionDescription();
	pCP->Send(StringUtil().convert_to_wstring(options_Desc));
}

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
	LogOut(_T("Request Data: "));
	LogOut(taskData);

	size_t pos = taskData.rfind(_T("\r\n"));
	taskData.erase(pos, 2); // Remove the ending tokens

	if(IConnectionPointPtr pCP = pEvent->GetConnectionPoint())
	{
		Ts::CmdLineMgr::pointer pCmdLineMgr = m_pCmdLinePaser->GetTaskCmdLineMgr();
		if(!pCmdLineMgr)
			return;

		bool ok = pCmdLineMgr->Parse(StringUtil().convert_to_string(taskData));
		if(!ok)
		{
			pCP->Send(_T("Failed to parse the options\r\n"));
			return;
		}

		if(pCmdLineMgr->HasUnrecognizedOption())
		{
			Ts::StringUtil util;

			const NString& invalidOpt = pCmdLineMgr->GetUnrecongnizedOption();

			CString prompt;
			prompt.Format(_T("Invalid options: %s\r\n\r\n"), util.convert_to_wstring(invalidOpt).data());
			pCP->Send(util.convert_to_wstring(prompt));

			SendDescription(pCP, pCmdLineMgr);

			return;
		}

		if(pCmdLineMgr->GetRecognizedOptionByName(OPT_HELP))
		{
			SendDescription(pCP, pCmdLineMgr);

			return;
		}

		CmdOptionPtr pVersion = pCmdLineMgr->GetRecognizedOptionByName(OPT_VERSION);
		CmdOptionPtr pName = pCmdLineMgr->GetRecognizedOptionByName(OPT_NAME);
		if(!pVersion)
		{
			pCP->Send(_T("Version isn't specified\r\n\r\n"));
			SendDescription(pCP, pCmdLineMgr);

			return;
		}

		if(!pName)
		{
			pCP->Send(_T("Name isn't specified\r\n\r\n"));
			SendDescription(pCP, pCmdLineMgr);

			return;
		}

		pCP->Send(_T("OK: Task is scheduled\r\n"));
		LogOut(_T("OK: Task is scheduled\r\n"));
	}
}

ConnectionMonitorSink::ConnectionMonitorSink(TextCommandParser* pCmdLinePaser) : m_pCmdLinePaser(pCmdLinePaser)
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
		LogOut(_T("New client connected.\r\n"));
		pCP->Send(MessageResource::GetWelcomeMesage());
		pCP->Send(_T("\r\n"));
		Ts::CmdLineMgr::pointer pCmdLineMgr = m_pCmdLinePaser->GetTaskCmdLineMgr();
		if(!pCmdLineMgr)
			return;

		SendDescription(pCP, pCmdLineMgr);
	}
}

void ConnectionMonitorSink::OnDisconnected(NetworkConnectionEvent* pEvent)
{
	LogOut(_T("Client disconnected.\n"));
}
