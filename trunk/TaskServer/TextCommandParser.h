#pragma once

#include "CmdLineMgr.h"


class TextCommandParser
{
public:
	TextCommandParser();

public:
	bool		ParseProgramOptions(int argc, const char* const argv[], unsigned short & portNumber);

private:
	void		PrintProgramHelp();

private:
	Ts::CmdLineMgr::pointer		m_pProgramCmdLineMgr;
	Ts::CmdLineMgr::pointer		m_pServerCmdLineMgr;

	Ts::CmdLineMgr::pointer		m_pTaskCmdLineMgr;
};