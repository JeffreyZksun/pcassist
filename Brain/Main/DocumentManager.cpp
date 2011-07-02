#include "StdAfx.h"
#include "DocumentManager.h"
#include "XmlIOStream.h"
#include "TaskManager.h"
#include "VariableManager.h"
#include "BrainApplication.h"

/************************************************************************/
/* The document schema/format is as below:
<DocRoot Version="1.0">
	<GlobalVariables>
		<Parameter> 
			<Name> </Name>
			<Value> </Value>
			<Comments> </Comments>
		</Parameter>
		<Parameter>...</Parameter>
		<Parameter>...</Parameter>
		...
	</GlobalVariables>

	<TaskList>
		<ActionId> (action id) </ActionId>
		<ActionId>...</ActionId>
		<ActionId>...</ActionId>
		...
	</TaskList>

	<Actions>
		<Action> 
			<Parameter>...</Parameter>
			<Parameter>...</Parameter>
			...
		</Action>
		<Action>...</Action>
		<Action>...</Action>
		...
	</Actions>

	<Conditions>
		<Condition> 
			<Parameter>...</Parameter>
			<Parameter>...</Parameter>
			...
		</Condition>
		<Condition>...</Condition>
		<Condition>...</Condition>
		...
	</Conditions>

</DocRoot>
*/
/************************************************************************/

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

#define DOC_ORIGINAL_VERSION 1
#define DOC_CURRENT_VERSION 1

#define DocRootNode _T("DocRoot")
#define VERSION_ATTR _T("Version")

bool DocumentManager::XmlIn(const BrainApplication* pBrainApp)
{
	if(NULL == pBrainApp)
		return false;
	ASSERT(pBrainApp != NULL);

	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(true);
	bool bRet = pXmlIOStream->Load(mDocumentName); // Load root
	ASSERT(bRet);
	if(!bRet)
		return false;

	{
		// The pointer has already points to the root. Don't need to move.
		//XmlIOStreamBeginNodeStack stack(pXmlIOStream, DocRootNode);

		// version
		CString docVersion;
		bool bExist = pXmlIOStream->ReadNodeAttribute(VERSION_ATTR, docVersion);
		if(bExist)
		{
			unsigned int ver = _ttoi(docVersion);
			pXmlIOStream->SetDocVersion(ver);
		}
		else
		{
			pXmlIOStream->SetDocVersion(DOC_ORIGINAL_VERSION);
		}

		// Load variable manager
		pBrainApp->GetVariableManager()->XmlIn(pXmlIOStream);

		// Load task manager
		pBrainApp->GetTaskManager()->XmlIn(pXmlIOStream);
	}

	::CoUninitialize();

	return bRet;
}

bool DocumentManager::XmlOut(const BrainApplication* pBrainApp)
{
	if(NULL == pBrainApp)
		return false;
	ASSERT(pBrainApp != NULL);

	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(false);
	pXmlIOStream->SetDocVersion(DOC_CURRENT_VERSION);

	{
		// Save root
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, DocRootNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;

		// version
		CString docVersion;
		docVersion.Format(_T("%u"), pXmlIOStream->GetDocVersion());
		pXmlIOStream->WriteNodeAttribute(VERSION_ATTR, docVersion);

		// Save variable manager
		pBrainApp->GetVariableManager()->XmlOut(pXmlIOStream);

		// Save task manager
		pBrainApp->GetTaskManager()->XmlOut(pXmlIOStream);
	}

	bool bRet = pXmlIOStream->Save(mDocumentName);

	::CoUninitialize();

	return bRet;
}