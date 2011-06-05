#include "StdAfx.h"
#include "ParameterObject.h"


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

bool ParameterObject::IsParameterValid(const Parameter& para) const
{
	return true;
}
