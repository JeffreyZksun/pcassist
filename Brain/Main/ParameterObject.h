#pragma once
#include <map>
#include "Parameter.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class BRAINEXPORT ParameterObject
{
public:
    ParameterObject(void);
    virtual ~ParameterObject(void);

public:
    typedef std::map<CString, Parameter> ParameterMap;

    void				AddParameter(const Parameter& para);
    bool				GetParameter(const CString& paraName, Parameter& para) const;

protected:
	virtual bool		IsParameterValid(const Parameter& para) const;

private:
    
    ParameterMap mParaMap;
};

#pragma warning( pop ) 
