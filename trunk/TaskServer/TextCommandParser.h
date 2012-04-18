#pragma once

#include "CmdLineMgr.h"


#define OPT_HELP ("help")

// m_pProgramCmdLineMgr
#define PRODUCT_VERSION _T("(v1.0)")
#define OPT_PORT ("port") // Read FILE as the task schema.

// m_pServerCmdLineMgr
#define OPT_QUIT ("quit")
#define OPT_USERS ("users")
#define OPT_TASKS ("tasks")

// m_pTaskCmdLineMgr
#define OPT_VERSION ("version")
#define OPT_NAME ("name")


class TextCommandParser
{
public:
	TextCommandParser();

public:
	bool						ParseProgramOptions(int argc, const char* const argv[], unsigned short & portNumber);
	Ts::CmdLineMgr::pointer		GetProgramCmdLineMgr() const;
	Ts::CmdLineMgr::pointer		GetServerCmdLineMgr() const;
	Ts::CmdLineMgr::pointer		GetTaskCmdLineMgr() const;

private:
	void		PrintProgramHelp();

private:
	Ts::CmdLineMgr::pointer		m_pProgramCmdLineMgr;
	Ts::CmdLineMgr::pointer		m_pServerCmdLineMgr;

	Ts::CmdLineMgr::pointer		m_pTaskCmdLineMgr;
};