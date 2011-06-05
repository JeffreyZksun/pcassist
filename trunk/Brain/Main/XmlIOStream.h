#pragma once

#include "XmlNodeWrapper.h"

class XmlIOStream
{
public:
	XmlIOStream(bool bIsRead);
	~XmlIOStream(void);

public:
	// write
	bool		BeginNode(const CString& nodeName);
	bool		CloseNode();
	bool		SetNodeText(const CString& text);
	bool		GetNodeText(CString& text);

public:
	void		Clear();
	bool		Load(const CString& docName);
	bool		Save(const CString& docName);

private:
	bool	mbIsRead;

	MSXML2::IXMLDOMNodePtr	mpCurrentNode;
	CXmlDocumentWrapper		mDocumentWrapper;
};

class XmlIOStreamBeginNodeStack
{
public:
	XmlIOStreamBeginNodeStack(XmlIOStream*, const CString& );
	~XmlIOStreamBeginNodeStack();

private:
	XmlIOStream* mpStream;
};
