#pragma once

class IXmlIOStream
{
public:
	virtual ~IXmlIOStream(void){};

public:
	// ToDo - we should replace the <> in the data.
	// Read
	virtual bool		ReadNode(const CString& nodeName) = 0;
	virtual bool		ReadNode(const CString& nodeName, int index) = 0;
	virtual bool		ReadNodeText(CString& text) = 0;
	virtual bool		ReadNodeAttribute(const CString& attrName, CString& attrValue) = 0;

	// Write
	virtual bool		WriteNode(const CString& nodeName) = 0;
	virtual bool		WriteNodeText(const CString& text) = 0;
	virtual bool		WriteNodeAttribute(const CString& attrName, const CString& attrValue) = 0;

	virtual bool		CloseNode() = 0;

	virtual bool		IsReadStream() const = 0;

	virtual void		SetDocVersion(unsigned int ver) = 0;
	virtual unsigned int GetDocVersion() const = 0;

public:
	virtual bool		Load(const CString& docName) = 0;
	virtual bool		Save(const CString& docName) = 0;
};
