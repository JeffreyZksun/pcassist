#pragma once
#include "BrainSystem.h"
#include "IDatabaseObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class XmlIOStream;

//////////////////////////////////////////////////////////////////////////
// ComplexString
//////////////////////////////////////////////////////////////////////////

// This class should work as a POD type. The operator = is deep copy.
class BRAINEXPORT ComplexString
{
public:
    ComplexString(void);
    ComplexString(const CString& variableString);
    ~ComplexString(void);

    void				SetRawString(const CString& variableString);
    const CString&		GetRawtring() const;
    CString				GetEvaluatedString() const;

private:
    CString				mRawVariableString; // %AppPath%
};

// This class should work as a POD type. The operator = is deep copy.
class BRAINEXPORT Parameter : IDataBaseObject
{
public:
    Parameter();
    Parameter(const CString& name);
    Parameter(const CString& name, const CString& value);

public:
    const CString&  GetName() const;

    void            SetValue(const CString& value);
    const CString&  GetRawValue() const;
    const CString   GetEvaluatedValue() const;

    void            SetComments(const CString& comments);
    const CString&  GetComments() const;

	virtual bool	XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool	XmlOut(XmlIOStream* pXmlIOStream) const;

private:
    // 
    CString         mName;
    ComplexString   mValue;
    CString         mComments;
};

#pragma warning( pop ) 

