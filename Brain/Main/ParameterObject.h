#pragma once
#include <map>
#include "Parameter.h"

class BRAINEXPORT ParameterObject
{
public:
    ParameterObject(void);
    virtual ~ParameterObject(void);

public:
    typedef std::map<CString, Parameter> ParameterMap;

    void        AddParameter(const Parameter& para);
    bool        GetParameter(const CString& paraName, Parameter& para) const;

private:
    
    ParameterMap mParaMap;
};

