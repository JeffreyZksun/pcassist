#include "StdAfx.h"
#include "DocumentManager.h"
#include "XmlIOStream.h"
#include "TaskManager.h"
#include "VariableManager.h"

/************************************************************************/
/* The document schema/format is as below:
<DocRoot>
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

#define DocRootNode _T("DocRoot")

bool DocumentManager::XmlIn()
{
	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(true);
	bool bRet = pXmlIOStream->Load(mDocumentName); // Load root
	ASSERT(bRet);
	if(!bRet)
		return false;

	{
		// The pointer has already points to the root. Don't need to move.
		//XmlIOStreamBeginNodeStack stack(pXmlIOStream, DocRootNode);

		// Load variable manager
		VariableManager::Get()->XmlIn(pXmlIOStream);

		// Load task manager
		TaskManager::Get()->XmlIn(pXmlIOStream);
	}

	::CoUninitialize();

	return bRet;
}

bool DocumentManager::XmlOut()
{
	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(false);

	{
		// Save root
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, DocRootNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;

		// Save variable manager
		VariableManager::Get()->XmlOut(pXmlIOStream);

		// Save task manager
		TaskManager::Get()->XmlOut(pXmlIOStream);
	}

	bool bRet = pXmlIOStream->Save(mDocumentName);

	::CoUninitialize();

	return bRet;
}