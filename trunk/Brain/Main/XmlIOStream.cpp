#include "StdAfx.h"
#include "XmlIOStream.h"

XmlIOStream::XmlIOStream(bool bIsRead) : mbIsRead(bIsRead), mpCurrentNode(NULL), mDocumentWrapper()
{

}

XmlIOStream::~XmlIOStream(void)
{
	
}
void XmlIOStream::Clear()
{

}

// Only for traverse the brothers when read.
bool XmlIOStream::BeginNode(const CString& nodeName, int index)
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

	if(index > nodeListWrapper.Count())
		return false;

	mpCurrentNode = nodeListWrapper.Node(index);
	ASSERT(mpCurrentNode != NULL);

	return true;
}

bool XmlIOStream::BeginNode(const CString& nodeName)
{
	if(!mbIsRead)
	{		
		if(NULL == mpCurrentNode) // This is the first node
		{
			mpCurrentNode = mDocumentWrapper.AppendChild(nodeName);
		}
		else
		{
			CXmlNodeWrapper nodeWrapper(mpCurrentNode);
			mpCurrentNode = nodeWrapper.AppendNode(nodeName);
		}

		ASSERT(mpCurrentNode != NULL);
	}
	else
	{
		ASSERT(mpCurrentNode != NULL);
		if(NULL == mpCurrentNode)
			return false;

		CXmlNodeWrapper nodeWrapper(mpCurrentNode);
		mpCurrentNode = nodeWrapper.GetNode(nodeName);
	}

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

bool XmlIOStream::SetNodeText(const CString& text)
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

bool XmlIOStream::GetNodeText(CString& text)
{
	ASSERT(mpCurrentNode != NULL);
	if(NULL == mpCurrentNode)
		return false;
	CXmlNodeWrapper nodeWrapper(mpCurrentNode);
	text = nodeWrapper.GetText();

	return true;
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
	BOOL bRet = mDocumentWrapper.Save(docName);
	ASSERT(TRUE == bRet);

	return TRUE == bRet;
}

XmlIOStreamBeginNodeStack::XmlIOStreamBeginNodeStack(XmlIOStream* pStream, const CString& nodeName)
: mpStream(pStream)
{
	if(mpStream != NULL)
		mpStream->BeginNode(nodeName);
}

XmlIOStreamBeginNodeStack::~XmlIOStreamBeginNodeStack()
{
	if(mpStream != NULL)
		mpStream->CloseNode();
}
