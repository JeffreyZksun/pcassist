#pragma once

#include "IXmlIOStream.h"

class XmlIOStreamImp;

class XmlIOStream : IXmlIOStream
{
public:
	XmlIOStream(bool bIsRead);
	virtual ~XmlIOStream(void);

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
	XmlIOStreamImp*		m_pImp;
};

class XmlIOStreamBeginNodeStack
{
public:
	XmlIOStreamBeginNodeStack(XmlIOStream*, const CString& );
	~XmlIOStreamBeginNodeStack();

	bool			IsSuccess();

private:
	XmlIOStream*	mpStream;
	bool			mbSucc;
};
