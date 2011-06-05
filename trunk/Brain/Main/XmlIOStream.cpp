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

bool XmlIOStream::BeginNode(const CString& nodeName)
{
	if(!mbIsRead)
	{		
		if(NULL == mpCurrentNode) // This is the firt node
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
		return false;
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
