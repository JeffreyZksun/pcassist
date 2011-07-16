#pragma once

using namespace System::Collections::Generic;

public ref class ExternalTool
{
public:
	ExternalTool(System::String^ title, System::String^ cmd, System::String^ par, System::String^ dir);

	System::String^ GetTitle();
	System::String^ GetCommand();
	System::String^ GetParameter();
	System::String^ GetWorkingDirectoty();

private:
	//System::String^ m_ActionId;
	System::String^ m_Title;
	System::String^ m_Command;
	System::String^ m_Parameter;
	System::String^ m_WorkingDirectoty;
};

public ref class ExternalToolManager
{
public:
	ExternalToolManager(void);

	bool Save(System::String^ fileName);
	bool Load(System::String^ fileName);


	void Add(ExternalTool^ extTool);
	void Remove(ExternalTool^ extTool);

	List<ExternalTool^>^ GetAllExternalTools();


private:
	List<ExternalTool^>^ m_ExtTools;


};


