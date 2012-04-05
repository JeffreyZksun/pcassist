#include "StdAfx.h"
#include "ParameterTableImp.h"
#include "XmlIOStream.h"
#include <algorithm>


ParameterTableImp::ParameterTableImp(ParameterTable* pSelf)
    : m_pSelf(pSelf), mParaList()
{
}

ParameterTableImp::~ParameterTableImp(void)
{
	for(ParameterList::iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		delete (*it);
	}

	mParaList.clear();
}

void ParameterTableImp::AddParameter(const Parameter& para)
{
    CString name = para.GetName();
    name.MakeLower();
    
    // If exist, update it.
	for(ParameterList::iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if((*it)->GetName().CompareNoCase(name) == 0)
		{
			(*it)->SetValue(para.GetRawValue());
			(*it)->SetComments(para.GetComments());
			return;
		}
	}

	Parameter* pNewPara = new Parameter(para);

    // Add new one
	mParaList.push_back(pNewPara);
}

bool ParameterTableImp::GetParameter(const CString& paraName, Parameter& para) const
{
    CString name = paraName;
    name.MakeLower();

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if((*it)->GetName().CompareNoCase(name) == 0)
		{
			para = *(*it);
			return true;
		}
	}

    // Not found
    return false;
}

bool ParameterTableImp::GetParameter(unsigned int index, Parameter& para) const
{
	if(index >= static_cast<unsigned int>(mParaList.size()))
		return false;

	int pos = 0;
	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if(pos == index)
		{
			para = *(*it);
			break;
		}
		pos++;
	}

	return true;
}

const Parameter* ParameterTableImp::GetParameter(const CString& paraName) const
{
	const Parameter* pResult = NULL;

	CString name = paraName;
	name.MakeLower();

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		if((*it)->GetName().CompareNoCase(name) == 0)
		{
			pResult = (*it);
			break;
		}
	}

	return pResult;
}

unsigned int ParameterTableImp::GetParameterLength() const
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

bool ParameterTableImp::XmlIn(XmlIOStream* pXmlIOStream)
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

bool ParameterTableImp::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	

	for(ParameterList::const_iterator it = mParaList.begin(); it != mParaList.end(); ++it)
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ParameterNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		(*it)->XmlOut(pXmlIOStream);
	}

	return true;
}
