#include "StdAfx.h"
#include "Parameter.h"
#include "VariableManager.h"

//////////////////////////////////////////////////////////////////////////
// ComplexString
//////////////////////////////////////////////////////////////////////////

ComplexString::ComplexString(void)
    : mRawVariableString()
{
}

ComplexString::ComplexString(const CString& variableString)
    : mRawVariableString(variableString)
{

}

ComplexString::~ComplexString(void)
{
}

void ComplexString::SetRawString(const CString& variableString)
{
    mRawVariableString = variableString;
}

const CString& ComplexString::GetRawtring() const
{
    return mRawVariableString;
}

CString ComplexString::GetEvaluatedString() const
{
    CString evaluatedString = VariableManager::Get()->GetEvaluatedString(mRawVariableString);
    return evaluatedString;
}

//////////////////////////////////////////////////////////////////////////
// Parameter
//////////////////////////////////////////////////////////////////////////

Parameter::Parameter()
    : mName(), mValue(), mComments()
{

}
Parameter::Parameter(const CString& name)
    : mName(name), mValue(), mComments()
{
}

Parameter::Parameter(const CString& name, const CString& value)
    : mName(name), mValue(value), mComments()
{
}

Parameter::~Parameter(void)
{
}

const CString& Parameter::GetName() const
{
    return mName;
}

void Parameter::SetValue(const CString& value)
{
    mValue = value;
}

const CString&  Parameter::GetRawdValue() const
{
    return  mValue.GetRawtring();
}

const CString  Parameter::GetEvaluatedValue() const
{
    return  mValue.GetEvaluatedString();
}

void Parameter::SetComments(const CString& comments)
{
    mComments = comments;
}

const CString& Parameter::GetComments() const
{
    return mComments;
}