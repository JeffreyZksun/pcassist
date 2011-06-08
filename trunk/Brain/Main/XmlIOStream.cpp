#include "StdAfx.h"
#include "XmlIOStream.h"

XmlIOStream::XmlIOStream(bool bIsRead) : mbIsRead(bIsRead), mpCurrentNode(NULL), mDocumentWrapper()
{

}

XmlIOStream::~XmlIOStream(void)
{
	
}

// Only for traverse the brothers when read.
bool XmlIOStream::ReadNode(const CString& nodeName, int index)
{
	ASSERT(mbIsRead); 
	if(!mbIsRead)
		return false;

	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;

	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	MSXML2::IXMLDOMNodeListPtr pNodeList = nodeWrapper.FindNodes(nodeName);

	CXmlNodeListWrapper nodeListWrapper(pNodeList);

	if(index >= nodeListWrapper.Count())
		return false;

	MSXML2::IXMLDOMNodePtr	pNode = nodeListWrapper.Node(index);
	ASSERT(pNode != NULL);
	if(NULL == pNode)
		return false;

	mpCurrentNode = pNode;

	return true;
}

bool XmlIOStream::ReadNode(const CString& nodeName)
{
	ASSERT(mbIsRead);
	if(!mbIsRead)
		return false;

	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;

	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	MSXML2::IXMLDOMNodePtr	pNode = nodeWrapper.GetNode(nodeName);

	if(NULL == pNode)
		return false;

	mpCurrentNode = pNode;

	return true;
}

bool XmlIOStream::ReadNodeText(CString& text)
{
	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;

	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	text = nodeWrapper.GetText();

	return true;
}

bool XmlIOStream::WriteNode(const CString& nodeName)
{
	ASSERT(!mbIsRead);
	if(mbIsRead)
		return false;

	MSXML2::IXMLDOMNodePtr	pNode = NULL;

	if(NULL == mpCurrentNode) // This is the first node
	{
		pNode = mDocumentWrapper.AppendChild(nodeName);
	}
	else
	{
		CXmlNodeWrapper nodeWrapper(mpCurrentNode);
		pNode = nodeWrapper.AppendNode(nodeName);
	}

	ASSERT(pNode != NULL);
	if(NULL == pNode)
		return false;

	mpCurrentNode = pNode;

	return true;
}

bool XmlIOStream::WriteNodeText(const CString& text)
{
	ASSERT(!mbIsRead);
	if(mbIsRead)
		return false; // Can't write to the read stream.

	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;

	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	nodeWrapper.SetText(text);

	return true;
}

bool XmlIOStream::CloseNode()
{
	// Back to parent
	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;
	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	mpCurrentNode = nodeWrapper.Parent();

	ASSERT(mpCurrentNode != NULL);

	return true;
}

bool XmlIOStream::IsReadStream() const
{
	return mbIsRead;
}

bool XmlIOStream::Load(const CString& docName)
{
	BOOL bRet = mDocumentWrapper.Load(docName);
	ASSERT(TRUE == bRet);

	mpCurrentNode = mDocumentWrapper.AsNode();
	ASSERT(mpCurrentNode != NULL);

	return TRUE == bRet;
}

bool XmlIOStream::Save(const CString& docName)
{
	if(!mDocumentWrapper.Interface())
		return false;

	// Use the xslt to indent the xml nodes.
	// http://social.msdn.microsoft.com/Forums/en-IE/xmlandnetfx/thread/61f88cf8-c019-423b-9a88-a065a4b0566d
	CXmlDocumentWrapper xslt;

	const CString strXslt = _T("<?xml version='1.0' encoding='UTF-8'?>\n\
		<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>\n\
		<xsl:output method='xml' version='1.0' encoding='UTF-8' indent='yes'/>\n\
		<xsl:template match='@* | node()'>\n\
		<xsl:copy>\n\
		<xsl:apply-templates select='@* | node()' />\n\
		</xsl:copy>\n\
		</xsl:template>\n\
		</xsl:stylesheet>");
	BOOL bRet = xslt.LoadXML(strXslt);
	ASSERT(TRUE == bRet);
	if(FALSE == bRet)
		return false;

	mDocumentWrapper.Interface()->transformNodeToObject(xslt.Interface(),CComVariant(mDocumentWrapper.Interface()));

	bRet = mDocumentWrapper.Save(docName);
	ASSERT(TRUE == bRet);

	return TRUE == bRet;
}

XmlIOStreamBeginNodeStack::XmlIOStreamBeginNodeStack(XmlIOStream* pStream, const CString& nodeName)
: mpStream(pStream), mbSucc(false)
{
	if(mpStream != NULL)
	{
		if(mpStream->IsReadStream())
			mbSucc = mpStream->ReadNode(nodeName);
		else
			mbSucc = mpStream->WriteNode(nodeName);
	}
}

XmlIOStreamBeginNodeStack::~XmlIOStreamBeginNodeStack()
{
	if(mpStream != NULL && mbSucc)
		mpStream->CloseNode();
}

bool XmlIOStreamBeginNodeStack::IsSuccess()
{
	return mbSucc;
}