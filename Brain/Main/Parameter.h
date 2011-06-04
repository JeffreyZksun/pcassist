#pragma once
#include "BrainSystem.h"

//////////////////////////////////////////////////////////////////////////
// ComplexString
//////////////////////////////////////////////////////////////////////////

// Define a POD type
class BRAINEXPORT ComplexString
{
public:
    ComplexString(void);
    ComplexString(const CString& variableString);
    ~ComplexString(void);

    void    SetRawString(const CString& variableString);
    const CString& GetRawtring() const;
    CString GetEvaluatedString();

private:
    CString mRawVariableString; // %AppPath%
};

// This class should work as a POD type. It is copied by using the operator = everywhere.
class BRAINEXPORT Parameter
{
public:
    Parameter();
    Parameter(const CString& name);
    Parameter(const CString& name, const CString& value);
    ~Parameter(void); // Note: POD can't be virtual.

public:
    const CString&  GetName() const;

    void            SetValue(const CString& value);
    const CString&  GetRawdValue() const;
    const CString   GetEvaluatedValue();

    void            SetComments(const CString& comments);
    const CString&  GetComments() const;

private:
    // Note: POD can't have pointer.
    CString         mName;
    ComplexString   mValue;
    CString         mComments;
};


