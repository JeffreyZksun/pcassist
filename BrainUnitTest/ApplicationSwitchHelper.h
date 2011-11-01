#pragma once

class BrainApplication;

class ApplicationSwitchHelper
{
public:
	ApplicationSwitchHelper();
	~ApplicationSwitchHelper();

private:
	BrainApplication* pCurrentApp;
	BrainApplication* pPreviousApp;
};


