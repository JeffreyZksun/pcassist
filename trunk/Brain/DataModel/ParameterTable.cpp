#include "StdAfx.h"
#include "ParameterTable.h"
#include "ParameterTableImp.h"



ParameterTable::ParameterTable(void)
    : m_pImp (new ParameterTableImp(this))
{
}

ParameterTable::~ParameterTable(void)
{
	if(m_pImp != NULL)
	{
		delete m_pImp;
		m_pImp = NULL;
	}
}

void ParameterTable::AddParameter(const Parameter& para)
{
	m_pImp->AddParameter(para);
}

bool ParameterTable::GetParameter(const CString& paraName, Parameter& para) const
{
	return 	m_pImp->GetParameter(paraName, para);
}

bool ParameterTable::GetParameter(unsigned int index, Parameter& para) const
{
	return 	m_pImp->GetParameter(index, para);
}

const Parameter* ParameterTable::GetParameter(const CString& paraName) const
{
	return 	m_pImp->GetParameter(paraName);
}

unsigned int ParameterTable::GetParameterLength() const
{
	return 	m_pImp->GetParameterLength();
}


bool ParameterTable::XmlIn(XmlIOStream* pXmlIOStream)
{
	return 	m_pImp->XmlIn(pXmlIOStream);
}

bool ParameterTable::XmlOut(XmlIOStream* pXmlIOStream) const
{
	return 	m_pImp->XmlOut(pXmlIOStream);
}
