#include "StdAfx.h"
#include "DocumentManager.h"
#include "XmlIOStream.h"

DocumentManager::DocumentManager(void)
{
}
DocumentManager::~DocumentManager(void)
{
}

void DocumentManager::SetDocumentName(const CString& docName)
{
	mDocumentName = docName;
}

bool DocumentManager::XmlIn()
{
	XmlIOStream* pXmlStream = new XmlIOStream(true);
	bool bRet = pXmlStream->Load(mDocumentName);

	// Load root
	// Load variable manager
	// Load task manager

	return bRet;
}
bool DocumentManager::XmlOut()
{
	XmlIOStream* pXmlStream = new XmlIOStream(false);

	// Save root
	// Save variable manager
	// Save task manager

	bool bRet = pXmlStream->Save(mDocumentName);

	return bRet;
}