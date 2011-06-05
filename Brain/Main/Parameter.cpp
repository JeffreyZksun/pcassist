#include "StdAfx.h"
#include "Parameter.h"
#include "VariableManager.h"
#include "XmlIOStream.h"

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

/************************************************************************
The data format is:
	<Name> </Name>
	<Value> </Value>
	<Comments> </Comments>

 If comment is empty, don't output.
************************************************************************/
bool Parameter::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	return true;
}

bool Parameter::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("Name"));
		pXmlIOStream->SetNodeText(mName);
	}

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("Value"));
		pXmlIOStream->SetNodeText(mValue.GetRawtring());
	}
	
	if(mComments.GetLength() != 0)
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("Comments"));
		pXmlIOStream->SetNodeText(mComments);
	}

	return true;
}