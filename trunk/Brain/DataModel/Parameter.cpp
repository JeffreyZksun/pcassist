#include "StdAfx.h"
#include "Parameter.h"
#include "ParameterImp.h"


Parameter::Parameter()
    : m_pImp (new ParameterImp(this))
{

}

Parameter::Parameter(const CString& name)
    : m_pImp (new ParameterImp(this, name))
{
}

Parameter::Parameter(const CString& name, const CString& value)
    : m_pImp (new ParameterImp(this, name, value))
{
}


Parameter::Parameter(const Parameter& rSrc) : m_pImp (new ParameterImp(this, rSrc.GetName(), rSrc.GetRawValue()))
{
	m_pImp->SetComments(rSrc.GetComments());
}

Parameter::~Parameter()
{
	if(m_pImp != NULL)
	{
		delete m_pImp;
		m_pImp = NULL;
	}
}

Parameter* Parameter::Clone() const
{
	Parameter* pNew = new Parameter(*this);
	return pNew;
}

Parameter& Parameter::operator= (const Parameter& rSrc)
{
	SetName(rSrc.GetName());
	SetValue(rSrc.GetRawValue());
	SetComments(rSrc.GetComments());

	return *this;
}

void  Parameter::SetName(const CString& name)
{
	m_pImp->SetName(name);
}

const CString& Parameter::GetName() const
{
    return m_pImp->GetName();
}

void Parameter::SetValue(const CString& value)
{
    m_pImp->SetValue(value);
}

const CString&  Parameter::GetRawValue() const
{
    return  m_pImp->GetRawValue();
}

const CString  Parameter::GetEvaluatedValue(const VariableManager* pVariableManager) const
{
    return   m_pImp->GetEvaluatedValue(pVariableManager);
}

void Parameter::SetComments(const CString& comments)
{
   m_pImp->SetComments(comments);
}

const CString& Parameter::GetComments() const
{
    return  m_pImp->GetComments();
}

bool Parameter::XmlIn(XmlIOStream* pXmlIOStream)
{
	return  m_pImp->XmlIn(pXmlIOStream);
}

bool Parameter::XmlOut(XmlIOStream* pXmlIOStream) const
{
	return  m_pImp->XmlOut(pXmlIOStream);
}