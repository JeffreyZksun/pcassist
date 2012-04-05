#pragma once

#include "IDataBaseObject.h"

class XmlIOStream;
class IOSProvider;
class VariableManagerImp;
class Parameter;

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT VariableManager : public IDataBaseObject
{
public:
    VariableManager(IOSProvider* pOSProvider);
    ~VariableManager(void);

    CString				GetEvaluatedString(const CString& variableString) const;
	void				AddUserParameter(const Parameter& para);
	bool				GetParameter(const CString& paraName, Parameter& para) const;


	virtual bool		XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool		XmlOut(XmlIOStream* pXmlIOStream) const;

private:
	VariableManagerImp*	m_pImp;
};



