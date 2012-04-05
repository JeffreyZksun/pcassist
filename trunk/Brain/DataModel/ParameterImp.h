#pragma once

class XmlIOStream;
class VariableManager;
class Parameter;

//////////////////////////////////////////////////////////////////////////
// ComplexString
//////////////////////////////////////////////////////////////////////////

// This class should work as a POD type. The operator = is deep copy.
class ComplexString
{
public:
    ComplexString(VariableManager* pVariableManager = NULL);
    ComplexString(const CString& variableString, VariableManager* pVariableManager = NULL);
    ~ComplexString(void);

    void				SetRawString(const CString& variableString);
    const CString&		GetRawtring() const;
    CString				GetEvaluatedString(const VariableManager* pVariableManager) const;

private:
    CString				mRawVariableString; // %AppPath%
};

// This class should work as a POD type. The operator = is deep copy.
class ParameterImp
{
public:
    ParameterImp(Parameter* pSelf);
    ParameterImp(Parameter* pSelf, const CString& name);
    ParameterImp(Parameter* pSelf, const CString& name, const CString& value);

public:
	void			SetName(const CString& name);
    const CString&  GetName() const;

    void            SetValue(const CString& value);
    const CString&  GetRawValue() const;
    const CString   GetEvaluatedValue(const VariableManager* pVariableManager) const;

    void            SetComments(const CString& comments);
    const CString&  GetComments() const;

public:
	bool	XmlIn(XmlIOStream* pXmlIOStream);
	bool	XmlOut(XmlIOStream* pXmlIOStream) const;

private:
	Parameter*		m_pSelf;
    // 
    CString         mName;
    ComplexString   mValue;
    CString         mComments;
};



