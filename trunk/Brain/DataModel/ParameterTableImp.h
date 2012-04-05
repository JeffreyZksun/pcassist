#pragma once
#include <list>
#include "Parameter.h"

class XmlIOStream;
class ParameterTable;

class ParameterTableImp
{
public:
    ParameterTableImp(ParameterTable* pSelf);
    ~ParameterTableImp(void);

public:
    void				AddParameter(const Parameter& para);
	bool				GetParameter(const CString& paraName, Parameter& para) const;
	bool				GetParameter(unsigned int index, Parameter& para) const;

	const Parameter*	GetParameter(const CString& paraName) const;

	unsigned int		GetParameterLength() const;

public:
	bool				XmlIn(XmlIOStream* pXmlIOStream);
	bool				XmlOut(XmlIOStream* pXmlIOStream) const;


private:
	// Use the list to instead the map. We want to the parameters are shown as sequence they are added. 
	//typedef std::map<CString, Parameter> ParameterMap;
	typedef std::list<Parameter*> ParameterList;

private:
	ParameterTable*		m_pSelf;

    ParameterList		mParaList;
};


