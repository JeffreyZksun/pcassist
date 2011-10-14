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
	ParameterTable mParameterTable;
};



