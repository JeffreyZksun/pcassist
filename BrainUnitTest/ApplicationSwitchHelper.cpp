#include "StdAfx.h"
#include "ApplicationSwitchHelper.h"
#include "BrainApplication.h"


ApplicationSwitchHelper::ApplicationSwitchHelper(): pPreviousApp(NULL), pCurrentApp(new BrainApplication())
{
	// Use the temp application.
	pPreviousApp = BrainApplication::SetWorkingBrain(pCurrentApp);
}

ApplicationSwitchHelper::~ApplicationSwitchHelper()
{
	// Recover
	BrainApplication *pTempApp = BrainApplication::SetWorkingBrain(pPreviousApp);
	ASSERT(pTempApp == pCurrentApp);

	delete pCurrentApp;
	pCurrentApp = NULL;
}

