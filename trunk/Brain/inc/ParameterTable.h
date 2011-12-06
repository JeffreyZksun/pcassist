#pragma once
#include <list>
#include "Parameter.h"
#include "IDatabaseObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class XmlIOStream;

class BRAINEXPORT ParameterTable : IDataBaseObject
{
public:
    ParameterTable(void);
    virtual ~ParameterTable(void);

public:
    void				AddParameter(const Parameter& para);
	bool				GetParameter(const CString& paraName, Parameter& para) const;
	bool				GetParameter(unsigned int index, Parameter& para) const;

	const Parameter*	GetParameter(const CString& paraName) const;

	unsigned int		GetParameterLength() const;

public:
	virtual bool		XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool		XmlOut(XmlIOStream* pXmlIOStream) const;

protected:
	virtual bool		IsParameterValid(const Parameter& para) const;

private:

	// Use the list to instead the map. We want to the parameters are shown as sequence they are added. 
	//typedef std::map<CString, Parameter> ParameterMap;
	typedef std::list<Parameter> ParameterList;

    ParameterList	mParaList;
};

#pragma warning( pop ) 
