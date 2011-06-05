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
	bool		SetNodeValue(const CString& nodeName);

public:
	void		Clear();
	bool		Load(const CString& docName);
	bool		Save(const CString& docName);

private:
	bool	mbIsRead;

	MSXML2::IXMLDOMNodePtr	mpCurrentNode;
	CXmlDocumentWrapper		mDocumentWrapper;
};
