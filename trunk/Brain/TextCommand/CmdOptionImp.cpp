#include "stdafx.h"
#include "CmdOptionImp.h"

using namespace Ts;

CmdOptionImp::CmdOptionImp(CmdOption* pSelf, const NString& name, const NString& description, CmdOption::EValueType eType) 
    : m_pSelf(pSelf), m_Name(name), m_ShortName(0), m_Description(description), m_eType(eType), m_Value()
{

}

CmdOptionImp::CmdOptionImp(CmdOption* pSelf, const NString& name, char shortName, const NString& description, CmdOption::EValueType eType) 
    : m_pSelf(pSelf), m_Name(name), m_ShortName(shortName), m_Description(description), m_eType(eType), m_Value()
{

}

CmdOptionImp::~CmdOptionImp()
{

}

NString CmdOptionImp::GetLongAndShortName() const
{
    NString fullName = GetName();

    if(GetShortName() < 127 && GetShortName() > 0)
    {
        fullName.push_back(',');
        fullName.push_back(GetShortName());
    }

    return fullName;
}

const NString& CmdOptionImp::GetName() const
{
    return m_Name;
}

void CmdOptionImp::SetName(const NString& name)
{
    m_Name = name;
}

char CmdOptionImp::GetShortName() const
{
    return m_ShortName;

}

void CmdOptionImp::SetShortName(char shortName)
{
    m_ShortName = shortName;
}

const NString& CmdOptionImp::GetDescription() const
{
    return m_Description;

}

void CmdOptionImp::SetDescription(const NString& description)
{
    m_Description = description;

}

const NString& CmdOptionImp::GetValue() const
{
    return m_Value;

}

void CmdOptionImp::SetValue(const NString& value)
{
    m_Value = value;

}

CmdOption::EValueType CmdOptionImp::GetValueType() const
{
	return m_eType;
}

void CmdOptionImp::SetValueType(CmdOption::EValueType eType)
{
	m_eType = eType;
}