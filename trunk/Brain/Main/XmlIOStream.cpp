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
		//CXmlNodeWrapper nodeWrapper(nodeName);
	}

	return false;
}
bool XmlIOStream::CloseNode()
{
	// Back to parent
	return false;
}

bool XmlIOStream::SetNodeValue(const CString& nodeName)
{
	return false;
}

bool XmlIOStream::Load(const CString& docName)
{
	//return mDocumentWrapper.Load(docName);
	return false;
}

bool XmlIOStream::Save(const CString& docName)
{
	//return mDocumentWrapper.Save(docName);
	return false;
}

