#include "StdAfx.h"
#include "XmlIOStream.h"

XmlIOStream::XmlIOStream(bool bIsRead) : mbIsRead(bIsRead)
{
}

XmlIOStream::~XmlIOStream(void)
{
}
void XmlIOStream::Clear()
{

}
bool XmlIOStream::Load(const CString& docName)
{
	return false;
}

bool XmlIOStream::Save(const CString& docName)
{
	return false;
}

