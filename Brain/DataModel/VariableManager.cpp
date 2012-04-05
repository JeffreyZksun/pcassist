#include "StdAfx.h"
#include "VariableManager.h"
#include "VariableManagerImp.h"

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

VariableManager::VariableManager(IOSProvider* pOSProvider) : m_pImp (new VariableManagerImp(this, pOSProvider))
{

}

VariableManager::~VariableManager(void)
{
	if(m_pImp != NULL)
	{
		delete m_pImp;
		m_pImp = NULL;
	}
}

 CString VariableManager::GetEvaluatedString(const CString& variableString) const
 {     
     return m_pImp->GetEvaluatedString(variableString);
 }

 void VariableManager::AddUserParameter(const Parameter& para)
 {
	m_pImp->AddUserParameter(para);
 }

 bool VariableManager::GetParameter(const CString& paraName, Parameter& para) const
 {
	 return m_pImp->GetParameter(paraName, para);
 }

 
bool VariableManager::XmlIn(XmlIOStream* pXmlIOStream)
{
	return m_pImp->XmlIn(pXmlIOStream);
}

bool VariableManager::XmlOut(XmlIOStream* pXmlIOStream) const
{
	return m_pImp->XmlOut(pXmlIOStream);
}

