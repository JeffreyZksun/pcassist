#pragma once

#include "XmlNodeWrapper.h"

class XmlIOStream
{
public:
	XmlIOStream(bool bIsRead);
	~XmlIOStream(void);

public:
	// ToDo - we should replace the <> in the data.
	// Read
	bool		ReadNode(const CString& nodeName);
	bool		ReadNode(const CString& nodeName, int index);
	bool		ReadNodeText(CString& text);

	// Write
	bool		WriteNode(const CString& nodeName);
	bool		WriteNodeText(const CString& text);

	bool		CloseNode();

	bool		IsReadStream() const;

public:
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

	bool			IsSuccess();

private:
	XmlIOStream*	mpStream;
	bool			mbSucc;
};
