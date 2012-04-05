#include "StdAfx.h"
#include "ParameterImp.h"
#include "VariableManager.h"
#include "XmlIOStream.h"


//////////////////////////////////////////////////////////////////////////
// ComplexString
//////////////////////////////////////////////////////////////////////////

ComplexString::ComplexString(VariableManager* pVariableManager/* = NULL*/)
    : mRawVariableString()
{
}

ComplexString::ComplexString(const CString& variableString, VariableManager* pVariableManager/* = NULL*/)
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

CString ComplexString::GetEvaluatedString(const VariableManager* pVariableManager) const
{
	ASSERT(pVariableManager != NULL);

	if(NULL == pVariableManager)
		return mRawVariableString;

	const CString evaluatedString = pVariableManager->GetEvaluatedString(mRawVariableString);

    return evaluatedString;
}

//////////////////////////////////////////////////////////////////////////
// ParameterImp
//////////////////////////////////////////////////////////////////////////

ParameterImp::ParameterImp(Parameter* pSelf)
    : m_pSelf(pSelf), mName(), mValue(), mComments()
{

}

ParameterImp::ParameterImp(Parameter* pSelf, const CString& name)
    : m_pSelf(pSelf), mName(name), mValue(), mComments()
{
}

ParameterImp::ParameterImp(Parameter* pSelf, const CString& name, const CString& value)
    : m_pSelf(pSelf), mName(name), mValue(value), mComments()
{
}

const CString& ParameterImp::GetName() const
{
    return mName;
}

void  ParameterImp::SetName(const CString& name)
{
	mName = name;
}

void ParameterImp::SetValue(const CString& value)
{
    mValue = value;
}

const CString&  ParameterImp::GetRawValue() const
{
    return  mValue.GetRawtring();
}

const CString  ParameterImp::GetEvaluatedValue(const VariableManager* pVariableManager) const
{
    return  mValue.GetEvaluatedString(pVariableManager);
}

void ParameterImp::SetComments(const CString& comments)
{
    mComments = comments;
}

const CString& ParameterImp::GetComments() const
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

#define NameNode _T("Name")
#define ValueNode _T("Value")
#define CommentsNode _T("Comments")

bool ParameterImp::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, NameNode);
		ASSERT(stack.IsSuccess());
		if(stack.IsSuccess())
			pXmlIOStream->ReadNodeText(mName);
	}

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ValueNode);
		ASSERT(stack.IsSuccess());
		if(stack.IsSuccess())
		{
			CString rawStr;
			pXmlIOStream->ReadNodeText(rawStr);
			mValue.SetRawString(rawStr);
		}
	}

	{
		// Optional data.
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, CommentsNode);
		if(stack.IsSuccess())
			pXmlIOStream->ReadNodeText(mComments);
	}
	return true;
}

bool ParameterImp::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, NameNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		pXmlIOStream->WriteNodeText(mName);
	}

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ValueNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		pXmlIOStream->WriteNodeText(mValue.GetRawtring());
	}
	
	if(mComments.GetLength() != 0)
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, CommentsNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		pXmlIOStream->WriteNodeText(mComments);
	}

	return true;
}
