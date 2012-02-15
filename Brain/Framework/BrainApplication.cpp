#include "StdAfx.h"
#include "BrainApplication.h"
#include "TaskManager.h"
#include "BehaviorBodyFactory.h"
#include "VariableManager.h"
#include "DocumentManager.h"

#include "HostService.h"
#include "IBehaviorBuilder.h"


BrainApplication::BrainApplication()
		: mpTaskManager(new TaskManager())
		, mpBehaviorBodyFactory(new BehaviorBodyFactory())
		, mpVariableManager(new VariableManager())
		, mpHostService(new HostService()) // ToDo - This data should be set by client.
{
	Initialize();
}

BrainApplication::~BrainApplication()
{
	delete mpTaskManager;
	delete mpBehaviorBodyFactory;
	delete mpVariableManager;
}


static BrainApplication	defaultApp;
static BrainApplication* pCurrentApp = &defaultApp;

BrainApplication* BrainApplication::GetWorkingBrain()
{
	return pCurrentApp;
}

BrainApplication* BrainApplication::SetWorkingBrain(BrainApplication* pNewApp)
{
	ASSERT(pNewApp != NULL);
	if(NULL == pNewApp) 
		return NULL;

	BrainApplication* pPreviousApp = pCurrentApp;
	pCurrentApp = pNewApp;
	return pPreviousApp;
}

TaskManager* BrainApplication::GetTaskManager() const
{
	return mpTaskManager;
}

BehaviorBodyFactory* BrainApplication::GetBehaviorBodyFactory() const
{
	return mpBehaviorBodyFactory;
}

VariableManager* BrainApplication::GetVariableManager() const
{
	return mpVariableManager;
}

IOSProvider* BrainApplication::GetOSProvider() const
{
	if(mpHostService)
	{
		return mpHostService->GetOSProvider();
	}

	return NULL;
}

bool BrainApplication::XmlIn(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlIn(this);

	return bRet;
}

bool BrainApplication::XmlOut(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlOut(this);

	return bRet;
}

void BrainApplication::Initialize()
{
	if(mpHostService)
	{
		IBehaviorBuilder* pBuilder = mpHostService->GetBehaviorBuilder();
		pBuilder->InitializeBehaviorBodyFactory(GetBehaviorBodyFactory());
	}
}
