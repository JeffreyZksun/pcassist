#include "StdAfx.h"
#include "ApplicationSwitchHelper.h"
#include "BrainApplication.h"


static BrainApplication	defaultApp;
static BrainApplication* pCurrentApp = &defaultApp;

BrainApplication* GetWorkingBrain()
{
	return pCurrentApp;
}

BrainApplication* SetWorkingBrain(BrainApplication* pNewApp)
{
	ASSERT(pNewApp != NULL);
	if(NULL == pNewApp) 
		return NULL;

	BrainApplication* pPreviousApp = pCurrentApp;
	pCurrentApp = pNewApp;
	return pPreviousApp;
}


ApplicationSwitchHelper::ApplicationSwitchHelper(): pPreviousApp(NULL), pCurrentApp(new BrainApplication())
{
	// Use the temp application.
	pPreviousApp = SetWorkingBrain(pCurrentApp);
}

ApplicationSwitchHelper::~ApplicationSwitchHelper()
{
	// Recover
	BrainApplication *pTempApp = SetWorkingBrain(pPreviousApp);
	ASSERT(pTempApp == pCurrentApp);

	delete pCurrentApp;
	pCurrentApp = NULL;
}

