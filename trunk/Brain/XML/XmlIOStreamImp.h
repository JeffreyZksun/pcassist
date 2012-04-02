#pragma once

#include "XmlNodeWrapper.h"

class XmlIOStream;

class XmlIOStreamImp
{
public:
	XmlIOStreamImp(XmlIOStream* pSelf, bool bIsRead);
	~XmlIOStreamImp(void);

public:
	// ToDo - we should replace the <> in the data.
	// Read
	bool		ReadNode(const CString& nodeName);
	bool		ReadNode(const CString& nodeName, int index);
	bool		ReadNodeText(CString& text);
	bool		ReadNodeAttribute(const CString& attrName, CString& attrValue);

	// Write
	bool		WriteNode(const CString& nodeName);
	bool		WriteNodeText(const CString& text);
	bool		WriteNodeAttribute(const CString& attrName, const CString& attrValue);

	bool		CloseNode();

	bool		IsReadStream() const;

	void		SetDocVersion(unsigned int ver);
	unsigned int GetDocVersion() const;

public:
	bool		Load(const CString& docName);
	bool		Save(const CString& docName);

private:
	XmlIOStream*    m_pSelf;

	bool			mbIsRead;
	unsigned int	mDocVersion;

	MSXML2::IXMLDOMNodePtr	mpCurrentNode;
	CXmlDocumentWrapper		mDocumentWrapper;
};

class XmlIOStreamImpBeginNodeStack
{
public:
	XmlIOStreamImpBeginNodeStack(XmlIOStreamImp*, const CString& );
	~XmlIOStreamImpBeginNodeStack();

	bool			IsSuccess();

private:
	XmlIOStreamImp*	mpStream;
	bool			mbSucc;
};
