#include "StdAfx.h"
#include "ParameterTable.h"
#include "XmlIOStream.h"
#include <algorithm>


ParameterTable::ParameterTable(void)
    : mParaList()
{
}

ParameterTable::~ParameterTable(void)
{

}

void ParameterTable::AddParameter(const Parameter& para)
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

bool ParameterTable::GetParameter(const CString& paraName, Parameter& para) const
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

bool ParameterTable::GetParameter(unsigned int index, Parameter& para) const
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

const Parameter* ParameterTable::GetParameter(const CString& paraName) const
{
	const Parameter* pResult = NULL;

	CString name = paraName;
	name.MakeLower();

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if(it->GetName().CompareNoCase(name) == 0)
		{
			pResult = &(*it);
			break;
		}
	}

	return pResult;
}

unsigned int ParameterTable::GetParameterLength() const
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

bool ParameterTable::XmlIn(XmlIOStream* pXmlIOStream)
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

bool ParameterTable::XmlOut(XmlIOStream* pXmlIOStream) const
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

bool ParameterTable::IsParameterValid(const Parameter& para) const
{
	return true;
}
