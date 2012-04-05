#pragma once
#include "ParameterTable.h"

class VariableManager;
class XmlIOStream;
class IOSProvider;

//////////////////////////////////////////////////////////////////////////
// VariableManagerImp
//////////////////////////////////////////////////////////////////////////

class VariableManagerImp
{
public:
    VariableManagerImp(VariableManager* pSelf, IOSProvider* pOSProvider);
    ~VariableManagerImp(void);

    CString				GetEvaluatedString(const CString& variableString) const;
	void				AddUserParameter(const Parameter& para);
	bool				GetParameter(const CString& paraName, Parameter& para) const;
	//ParameterTable&		GetParameterTable();

	virtual bool		XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool		XmlOut(XmlIOStream* pXmlIOStream) const;

public:
    bool				GetNextVariable(const CString& variableString, CString& varItem) const;

private:
	// Add the supported global variables to the table.
	// This function is called when construct this manager.
	void				InitializeBuiltInGlobalVariables(IOSProvider* pOSProvider);

	void				AddBuiltinParameter(const Parameter& para);

	VariableManager*	Self() const;
private:
	VariableManager*	m_pSelf;

	ParameterTable		mUserParameterTable;
	ParameterTable		mBuiltinParameterTable; // Don't persist
};



