#include "StdAfx.h"
#include "ExternalTool.h"
#include <BrainApplication.h>
#include <TaskManager.h>

#define ET_TITLE _T("ET_Title")
#define ET_COMMAND _T("ET_Command")
#define ET_PARAMETER _T("ET_Paremeter")
#define ET_WORKINGDIRECTORY _T("ET_Directory")

ExternalTool::ExternalTool(System::String^ title, System::String^ cmd, System::String^ par, System::String^ dir) 
	: m_Title(title), m_Command(cmd), m_Parameter(par), m_WorkingDirectoty(dir)
{

}

System::String^ ExternalTool::GetTitle()
{
	return m_Title;
}

System::String^ ExternalTool::GetCommand()
{
	return m_Command;
}

System::String^ ExternalTool::GetParameter()
{
	return m_Parameter;
}

System::String^ ExternalTool::GetWorkingDirectoty()
{
	return m_WorkingDirectoty;
}

ExternalToolManager::ExternalToolManager()
{
	m_ExtTools = gcnew List<ExternalTool^>();
}

bool ExternalToolManager::Save(System::String^ fileName)
{
	BrainApplication::GetWorkingBrain()->GetTaskManager()->deleteRegisteredActions();
	for(int i = 0; i < m_ExtTools->Count; i++)
	{
		ExternalTool^ et = m_ExtTools[i];

		Action* pExtAction = new Action(_T("RunProcessAction")); // TaskManager will delete it.
		Parameter para1(ET_TITLE, CString(et->GetTitle()));
		Parameter para2(ET_COMMAND, CString(et->GetCommand()));
		Parameter para3(ET_PARAMETER, CString(et->GetParameter()));
		Parameter para4(ET_WORKINGDIRECTORY, CString(et->GetWorkingDirectoty()));

		pExtAction->AddParameter(para1);
		pExtAction->AddParameter(para2);
		pExtAction->AddParameter(para3);
		pExtAction->AddParameter(para4);
	}

	CString strFileName(fileName);
	bool bRet = BrainApplication::GetWorkingBrain()->XmlOut(strFileName);
	return bRet;
}

bool ExternalToolManager::Load(System::String^ fileName)
{
	CString strFileName(fileName);
	bool bRet = BrainApplication::GetWorkingBrain()->XmlIn(strFileName);

	
	for(size_t i = 0; i < BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionCount(); i++)
	{
		Action* pAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionByIndex(i);

		if(pAction != NULL)
		{
			System::String^ strTitle = nullptr;
			System::String^ strCmd = nullptr;
			System::String^ strPara = nullptr;
			System::String^ strDir = nullptr;

			Parameter para;
			bool bRet = pAction->GetParameter(ET_TITLE, para);
			if(!bRet)
				continue;

			{
				CString value = para.GetEvaluatedValue();
				strTitle = gcnew System::String(value);
			}

			bRet = pAction->GetParameter(ET_COMMAND, para);
			if(!bRet)
				continue;

			{
				CString value = para.GetEvaluatedValue();
				strCmd = gcnew System::String(value);
			}

			bRet = pAction->GetParameter(ET_PARAMETER, para);
			if(!bRet)
				continue;

			{
				CString value = para.GetEvaluatedValue();
				strPara = gcnew System::String(value);
			}

			bRet = pAction->GetParameter(ET_WORKINGDIRECTORY, para);
			if(!bRet)
				continue;

			{
				CString value = para.GetEvaluatedValue();
				strDir = gcnew System::String(value);
			}

			ExternalTool^ et = gcnew ExternalTool(strTitle, strCmd, strPara, strDir);
			m_ExtTools->Add(et);
		}
	}	

	return bRet;
}

void ExternalToolManager::Add(ExternalTool^ extTool)
{
	m_ExtTools->Add(extTool);
}

void ExternalToolManager::Remove(ExternalTool^ extTool)
{
	m_ExtTools->Remove(extTool);
}

List<ExternalTool^>^ ExternalToolManager::GetAllExternalTools()
{
	return m_ExtTools;
}