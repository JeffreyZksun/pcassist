#include "StdAfx.h"
#include "ParameterObject.h"
#include "XmlIOStream.h"
#include <algorithm>


ParameterObject::ParameterObject(void)
    : mParaList()
{
}

ParameterObject::~ParameterObject(void)
{

}

void ParameterObject::AddParameter(const Parameter& para)
{
	if(!IsParameterValid(para))
		return;

    CString name = para.GetName();
    name.MakeLower();
    
    // If exist, update it.
	for(ParameterList::iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if(it->GetName().CompareNoCase(name) == 0)
		{
			(*it) = para;
			return;
		}
	}

    // Add new one
	mParaList.push_back(para);
}

bool ParameterObject::GetParameter(const CString& paraName, Parameter& para) const
{
    CString name = paraName;
    name.MakeLower();

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if(it->GetName().CompareNoCase(name) == 0)
		{
			para = (*it);
			return true;
		}
	}

    // Not found
    return false;
}

bool ParameterObject::GetParameter(unsigned int index, Parameter& para) const
{
	if(index >= static_cast<unsigned int>(mParaList.size()))
		return false;

	int pos = 0;
	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if(pos == index)
		{
			para = *it;
			break;
		}
		pos++;
	}

	return true;
}

unsigned int ParameterObject::GetParameterLength() const
{
	return static_cast<unsigned int>(mParaList.size());
}

/************************************************************************
The data format is:
	<Parameter> ...</Parameter>
	<Parameter>...</Parameter>
	<Parameter>...</Parameter>
	...
************************************************************************/

#define ParameterNode _T("Parameter")

bool ParameterObject::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	{
		int index = 0;
		while(true)
		{		
			bool bHasParameter = pXmlIOStream->ReadNode(ParameterNode, index);
			if(!bHasParameter)
				break;

			Parameter newPara;
			bool bRet = newPara.XmlIn(pXmlIOStream);

			if(bRet)
				AddParameter(newPara);

			index++;

			pXmlIOStream->CloseNode();
		}
	}
	return true;
}

bool ParameterObject::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ParameterNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		it->XmlOut(pXmlIOStream);
	}

	return true;
}

bool ParameterObject::IsParameterValid(const Parameter& para) const
{
	return true;
}
