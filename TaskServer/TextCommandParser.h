#pragma once

#include "CmdLineMgr.h"


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