#pragma once
#include "ParameterObject.h"

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT VariableManager : public ParameterObject
{
public:
    VariableManager(void);
    ~VariableManager(void);

    static VariableManager* Get(); // Singleton

    CString GetEvaluatedString(const CString& variableString) const;

public:
    bool GetNextVariable(const CString& variableString, CString& varItem) const;
};



