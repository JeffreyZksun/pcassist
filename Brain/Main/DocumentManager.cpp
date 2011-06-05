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

bool DocumentManager::XmlIn()
{
	::CoInitialize(NULL);

	XmlIOStream* pXmlStream = new XmlIOStream(true);
	bool bRet = pXmlStream->Load(mDocumentName);

	// Load root
	// Load variable manager
	// Load task manager

	::CoUninitialize();

	return bRet;
}
bool DocumentManager::XmlOut()
{
	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(false);

	{
		// Save root
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("DocRoot"));

		// Save variable manager
		VariableManager::Get()->XmlOut(pXmlIOStream);

		// Save task manager
		TaskManager::Get()->XmlOut(pXmlIOStream);
	}

	bool bRet = pXmlIOStream->Save(mDocumentName);

	::CoUninitialize();

	return bRet;
}