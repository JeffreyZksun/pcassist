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
		bool bHasParameter = true;
		int index = 0;
		while(bHasParameter)
		{		
			bHasParameter = pXmlIOStream->ReadNode(ParameterNode, index);
			if(!bHasParameter)
				break;

			Parameter newPara;
			newPara.XmlIn(pXmlIOStream);

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
		it->XmlOut(pXmlIOStream);
	}

	return true;
}

bool ParameterObject::IsParameterValid(const Parameter& para) const
{
	return true;
}
