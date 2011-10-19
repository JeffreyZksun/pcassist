#pragma once
#include "ParameterTable.h"

class XmlIOStream;

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT VariableManager : public IDataBaseObject
{
public:
    VariableManager(void);
    ~VariableManager(void);

    CString GetEvaluatedString(const CString& variableString) const;
	ParameterTable& GetParameterTable();

	virtual bool XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool XmlOut(XmlIOStream* pXmlIOStream) const;

public:
    bool GetNextVariable(const CString& variableString, CString& varItem) const;

private:
	// Add the supported global variables to the table.
	// This function is called when construct this manager.
	void InitializeBuiltInGlobalVariables();
private:
	ParameterTable mParameterTable;
};



