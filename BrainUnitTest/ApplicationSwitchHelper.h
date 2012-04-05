#pragma once

class BrainApplication;


BrainApplication* GetWorkingBrain();
BrainApplication* SetWorkingBrain(BrainApplication* pNewApp);


class ApplicationSwitchHelper
{
public:
	ApplicationSwitchHelper();
	~ApplicationSwitchHelper();

private:
	BrainApplication* pCurrentApp;
	BrainApplication* pPreviousApp;
};


