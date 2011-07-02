#pragma once
#include "ParameterObject.h"

class XmlIOStream;

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT VariableManager : public ParameterObject
{
public:
    VariableManager(void);
    ~VariableManager(void);

    CString GetEvaluatedString(const CString& variableString) const;

	bool XmlIn(XmlIOStream* pXmlIOStream);
	bool XmlOut(XmlIOStream* pXmlIOStream) const;

public:
    bool GetNextVariable(const CString& variableString, CString& varItem) const;
};



