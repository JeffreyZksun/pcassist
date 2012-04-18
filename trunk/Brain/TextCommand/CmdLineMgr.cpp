#include "stdafx.h"
#include "CmdLineMgr.h"
#include "CmdLineMgrImp.h"

using namespace Ts;


CmdLineMgr::CmdLineMgr()
{
}

CmdLineMgr::~CmdLineMgr()
{
}

CmdLineMgr::pointer CmdLineMgr::Create()
{
	CmdLineMgr::pointer pNewObj(new CmdLineMgr());
	pNewObj->m_pImp.reset(new CmdLineMgrImp(pNewObj));

	return pNewObj;
}


bool CmdLineMgr::Parse(int argc, const char* const argv[])
{
    return m_pImp->Parse(argc, argv);
}

bool CmdLineMgr::Parse(const NString& optionString)
{
    return m_pImp->Parse(optionString);
}

bool CmdLineMgr::AddSupportedOption(CmdOptionPtr pOption)
{
    return m_pImp->AddSupportedOption(pOption);
}

CmdOptionPtr CmdLineMgr::GetRecognizedOptionByName(const NString& name) const
{
    return m_pImp->GetRecognizedOptionByName(name);
}

CmdOptionPtr CmdLineMgr::GetSupportedOptionByName(const NString& name) const
{
    return m_pImp->GetSupportedOptionByName(name);
}

bool CmdLineMgr::HasRecognizedOption() const
{
	return m_pImp->HasRecognizedOption();
}

bool CmdLineMgr::HasUnrecognizedOption() const
{
    return m_pImp->HasUnrecognizedOption();
}

const NString& CmdLineMgr::GetUnrecongnizedOption() const
{
    return m_pImp->GetUnrecongnizedOption();
}
NString	CmdLineMgr::GetOptionDescription() const
{
	return m_pImp->GetOptionDescription();
}