#include "stdafx.h"
#include "TextCommandParser.h"

#include "CmdOption.h"

#define PRODUCT_VERSION _T("(v1.0)")
#define OPT_PORT ("port") // Read FILE as the task schema.
#define OPT_HELP ("help")


TextCommandParser::TextCommandParser()
{
	// Initialize m_pProgramCmdLineMgr
	m_pProgramCmdLineMgr = Ts::CmdLineMgr::Create();
	{
		CmdOptionPtr pOption(new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue));
		bool ok = m_pProgramCmdLineMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption(OPT_PORT, 'P', "The server port"));
		bool ok = m_pProgramCmdLineMgr->AddSupportedOption(pOption);
	}

	// m_pServerCmdLineMgr
	m_pServerCmdLineMgr = Ts::CmdLineMgr::Create();


	m_pTaskCmdLineMgr = Ts::CmdLineMgr::Create();
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
		LogOut(prompt);
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


void TextCommandParser::PrintProgramHelp()
{
	const NString options_Desc = m_pProgramCmdLineMgr->GetOptionDescription();

	WString wstr(options_Desc.begin(), options_Desc.end());
	CString cstrDesc = wstr.c_str();	

	LogOut(_T("Usage: TaskServer [options...]\n"));

	LogOut(cstrDesc);

	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(PRODUCT_VERSION);
	LogOut(_T("\n"));
}