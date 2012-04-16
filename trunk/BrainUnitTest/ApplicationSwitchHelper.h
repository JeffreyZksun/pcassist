#pragma once

class TaskSystem;


TaskSystem* GetWorkingBrain();
TaskSystem* SetWorkingBrain(TaskSystem* pNewApp);


class ApplicationSwitchHelper
{
public:
	ApplicationSwitchHelper();
	~ApplicationSwitchHelper();

private:
	TaskSystem* pCurrentApp;
	TaskSystem* pPreviousApp;
};


