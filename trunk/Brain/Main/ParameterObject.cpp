#include "StdAfx.h"
#include "ParameterObject.h"
#include "XmlIOStream.h"


ParameterObject::ParameterObject(void)
    : mParaMap()
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
    ParameterMap::iterator it = mParaMap.find(name);
    if (it != mParaMap.end())
    {
        it->second = para;
        return;
    }

    // Add new one
    mParaMap.insert(std::make_pair(name, para));
}

bool ParameterObject::GetParameter(const CString& paraName, Parameter& para) const
{
    CString name = paraName;
    name.MakeLower();

    ParameterMap::const_iterator it = mParaMap.find(name);
    if (it != mParaMap.end())
    {
        para = it->second;
        return true;
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
			bHasParameter = pXmlIOStream->BeginNode(ParameterNode, index);
			if(!bHasParameter)
				break;

			Parameter newPara;
			newPara.XmlIn(pXmlIOStream);

			AddParameter(newPara);

			index++;
		}

		pXmlIOStream->CloseNode();
	}
	return true;
}

bool ParameterObject::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	

	for (ParameterMap::const_iterator it = mParaMap.begin(); it != mParaMap.end(); ++it)
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ParameterNode);
		(it->second).XmlOut(pXmlIOStream);
	}

	return true;
}

bool ParameterObject::IsParameterValid(const Parameter& para) const
{
	return true;
}
