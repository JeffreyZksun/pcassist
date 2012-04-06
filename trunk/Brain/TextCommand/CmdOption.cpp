#include "stdafx.h"
#include "CmdOption.h"
#include "CmdOptionImp.h"

using namespace Ts;

CmdOption::CmdOption(const NString& name, const NString& description) 
    : m_pImp(NULL)
{
    m_pImp = new CmdOptionImp(this, name, description);
}

CmdOption::CmdOption(const NString& name, char shortName, const NString& description) 
    : m_pImp(NULL)
{
     m_pImp = new CmdOptionImp(this, name, shortName, description);
}

CmdOption::~CmdOption()
{
    if(m_pImp != NULL)
    {
        delete m_pImp;
        m_pImp = NULL;
    }
}

NString CmdOption::GetLongAndShortName() const
{
    return m_pImp->GetLongAndShortName();
}

const NString& CmdOption::GetName() const
{
    return m_pImp->GetName();
}

void CmdOption::SetName(const NString& name)
{
    m_pImp->SetName(name);
}

char CmdOption::GetShortName() const
{
    return m_pImp->GetShortName();
}

void CmdOption::SetShortName(char shortName)
{
    m_pImp->SetShortName(shortName);
}

const NString& CmdOption::GetDescription() const
{
    return m_pImp->GetDescription();
}

void CmdOption::SetDescription(const NString& description)
{
    m_pImp->SetDescription(description);
}

const NString& CmdOption::GetValue() const
{
    return m_pImp->GetValue();
}

void CmdOption::SetValue(const NString& value)
{
    m_pImp->SetValue(value);
}