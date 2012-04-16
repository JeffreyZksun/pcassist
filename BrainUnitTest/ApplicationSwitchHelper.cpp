#include "StdAfx.h"
#include "ApplicationSwitchHelper.h"
#include "TaskSystem.h"


static TaskSystem	defaultApp;
static TaskSystem* pCurrentApp = &defaultApp;

TaskSystem* GetWorkingBrain()
{
	return pCurrentApp;
}

TaskSystem* SetWorkingBrain(TaskSystem* pNewApp)
{
	ASSERT(pNewApp != NULL);
	if(NULL == pNewApp) 
		return NULL;

	TaskSystem* pPreviousApp = pCurrentApp;
	pCurrentApp = pNewApp;
	return pPreviousApp;
}


ApplicationSwitchHelper::ApplicationSwitchHelper(): pPreviousApp(NULL), pCurrentApp(new TaskSystem())
{
	// Use the temp application.
	pPreviousApp = SetWorkingBrain(pCurrentApp);
}

ApplicationSwitchHelper::~ApplicationSwitchHelper()
{
	// Recover
	TaskSystem *pTempApp = SetWorkingBrain(pPreviousApp);
	ASSERT(pTempApp == pCurrentApp);

	delete pCurrentApp;
	pCurrentApp = NULL;
}

