#include "stdafx.h"
#include "TextCommandParser.h"

#include "CmdOption.h"


TextCommandParser::TextCommandParser()
{
	// Initialize m_pProgramCmdLineMgr
	m_pProgramCmdLineMgr = Ts::CmdLineMgr::Create();
	{
		CmdOptionPtr pOption(new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue));
		m_pProgramCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_PORT, 'P', "The server port"));
		m_pProgramCmdLineMgr->AddSupportedOption(pOption);
	}

	// m_pServerCmdLineMgr
	m_pServerCmdLineMgr = Ts::CmdLineMgr::Create();
	{
		CmdOptionPtr pOption(new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue));
		m_pServerCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_QUIT, 'Q', "Quit server"));
		m_pServerCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_USERS, 'U', "List the connected users"));
		m_pServerCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_USERS, 'T', "List the pending tasks"));
		m_pServerCmdLineMgr->AddSupportedOption(pOption);
	}

	// m_pTaskCmdLineMgr
	m_pTaskCmdLineMgr = Ts::CmdLineMgr::Create();
	{
		CmdOptionPtr pOption(new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue));
		m_pTaskCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_QUIT, 'Q', "Quit server"));
		m_pTaskCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_VERSION, 'V', "Version"));
		m_pTaskCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_NAME, 'N', "3p name for x86"));
		m_pTaskCmdLineMgr->AddSupportedOption(pOption);
	}
}

bool TextCommandParser::ParseProgramOptions(int argc, const char* const argv[], unsigned short & portNumber)
{
	const bool ok = m_pProgramCmdLineMgr->Parse(argc, argv);
	portNumber = 0;

	if(!ok)
	{
		LogOut(_T("Failed to parse the command line options\n\n"));
		PrintProgramHelp();

		return false;
	}

	if(m_pProgramCmdLineMgr->HasUnrecognizedOption())
	{
		const NString& invalidOpt = m_pProgramCmdLineMgr->GetUnrecongnizedOption();

		CString prompt;
		prompt.Format(_T("TaskServer: invalid options %s\n\n"), invalidOpt);
		Ts::StringUtil util;
		LogOut(util.convert_to_wstring(prompt));
		PrintProgramHelp();

		return false;
	}

	if(m_pProgramCmdLineMgr->GetRecognizedOptionByName(OPT_HELP))
	{
		PrintProgramHelp();

		return true;
	}

	CmdOptionPtr pPortOpt = m_pProgramCmdLineMgr->GetRecognizedOptionByName(OPT_PORT);
	if(!pPortOpt)
	{
		LogOut(_T("Error: server port isn't specified\n\n"));
		PrintProgramHelp();
		return false;
	}

	const NString& strPort = pPortOpt->GetValue();

	std::istringstream istr(strPort.c_str());
	istr >> portNumber;
	if(0 == portNumber)
	{
		LogOut(_T("Error: Invalid port\n\n"));
		PrintProgramHelp();
		return false;
	}

	return true;
}

Ts::CmdLineMgr::pointer	TextCommandParser::GetProgramCmdLineMgr() const
{
	return m_pProgramCmdLineMgr;
}

Ts::CmdLineMgr::pointer	TextCommandParser::GetServerCmdLineMgr() const
{
	return m_pServerCmdLineMgr;
}

Ts::CmdLineMgr::pointer TextCommandParser::GetTaskCmdLineMgr() const
{
	return m_pTaskCmdLineMgr;
}

void TextCommandParser::PrintProgramHelp()
{
	const NString options_Desc = m_pProgramCmdLineMgr->GetOptionDescription();

	Ts::StringUtil util;
	WString wstr;
	util.decode_utf8(options_Desc, wstr);

	LogOut(_T("Usage: TaskServer [options...]\n"));

	LogOut(wstr);

	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(PRODUCT_VERSION);
	LogOut(_T("\n"));
}