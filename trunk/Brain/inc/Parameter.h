#pragma once
#include "BrainSystem.h"
#include "IDatabaseObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class XmlIOStream;
class ParameterImp;
class VariableManager;

// This class should work as a POD type. The operator = is deep copy.
class BRAINEXPORT Parameter : IDataBaseObject
{
public:
	Parameter();
    Parameter(const CString& name);
    Parameter(const CString& name, const CString& value);

	Parameter(const Parameter& rSrc);
	
	virtual ~Parameter();

	Parameter* Clone() const;

	Parameter& operator= (const Parameter& rSrc);

public:
	void  SetName(const CString& name);
    const CString&  GetName() const;

    void            SetValue(const CString& value);
    const CString&  GetRawValue() const;
    const CString   GetEvaluatedValue(const VariableManager* pVariableManager) const;

    void            SetComments(const CString& comments);
    const CString&  GetComments() const;

	virtual bool	XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool	XmlOut(XmlIOStream* pXmlIOStream) const;

private:
    // 
    ParameterImp*	m_pImp;
};

#pragma warning( pop ) 

