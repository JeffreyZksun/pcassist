#include "stdafx.h"
#include "CmdLineMgr.h"
#include "CmdLineMgrImp.h"

using namespace Ts;


CmdLineMgr::CmdLineMgr() : m_pImp(NULL)
{
    m_pImp = new CmdLineMgrImp(this);
}

CmdLineMgr::~CmdLineMgr()
{
    if(m_pImp != NULL)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
}

bool CmdLineMgr::Parse(int argc, const char* const argv[])
{
    return m_pImp->Parse(argc, argv);
}

bool CmdLineMgr::Parse(NString optionString)
{
    return m_pImp->Parse(optionString);
}

bool CmdLineMgr::AddSupportedOption(CmdOption* pOption)
{
    return m_pImp->AddSupportedOption(pOption);
}

CmdOption* CmdLineMgr::GetRecognizedOptionByName(const NString& name) const
{
    return m_pImp->GetRecognizedOptionByName(name);
}

CmdOption* CmdLineMgr::GetSupportedOptionByName(const NString& name) const
{
    return m_pImp->GetSupportedOptionByName(name);
}

bool CmdLineMgr::HasUnrecognizedOption() const
{
    return m_pImp->HasUnrecognizedOption();
}

const NString& CmdLineMgr::GetUnrecongnizedOption() const
{
    return m_pImp->GetUnrecongnizedOption();
}