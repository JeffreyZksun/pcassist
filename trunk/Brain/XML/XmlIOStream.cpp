#include "StdAfx.h"
#include "XmlIOStream.h"
#include "XmlIOStreamImp.h"

XmlIOStream::XmlIOStream(bool bIsRead) : m_pImp(NULL)
{
	m_pImp = new XmlIOStreamImp(this, bIsRead);
}

XmlIOStream::~XmlIOStream(void)
{
	if(m_pImp)
	{
		delete m_pImp;
		m_pImp = NULL;
	}
}

// Only for traverse the brothers when read.
bool XmlIOStream::ReadNode(const CString& nodeName, int index)
{
	return m_pImp->ReadNode(nodeName, index);
}

bool XmlIOStream::ReadNode(const CString& nodeName)
{
	return m_pImp->ReadNode(nodeName);
}

bool XmlIOStream::ReadNodeText(CString& text)
{
	return m_pImp->ReadNodeText(text);
}

bool XmlIOStream::ReadNodeAttribute(const CString& attrName, CString& attrValue)
{
	return m_pImp->ReadNodeAttribute(attrName, attrValue);
}

bool XmlIOStream::WriteNode(const CString& nodeName)
{
	return m_pImp->WriteNode(nodeName);
}

bool XmlIOStream::WriteNodeText(const CString& text)
{
	return m_pImp->WriteNodeText(text);

}

bool XmlIOStream::WriteNodeAttribute(const CString& attrName, const CString& attrValue)
{
	return m_pImp->WriteNodeAttribute(attrName, attrValue);
}

bool XmlIOStream::CloseNode()
{
	return m_pImp->CloseNode();
}

bool XmlIOStream::IsReadStream() const
{
	return m_pImp->IsReadStream();
}

void XmlIOStream::SetDocVersion(unsigned int ver)
{
	m_pImp->SetDocVersion(ver);
}

unsigned int XmlIOStream::GetDocVersion() const
{
	return m_pImp->GetDocVersion();
}

bool XmlIOStream::Load(const CString& docName)
{
	return m_pImp->Load(docName);
}

bool XmlIOStream::Save(const CString& docName)
{
	return m_pImp->Save(docName);
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