// BrainUnitTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Parameter.h"
#include "Condition.h"
#include "Action.h"
#include "TaskManager.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "VariableManager.h"

void TestFileExistsCondition();
void TestParameterObject();
void TestFolderExistsCondition();

int _tmain(int argc, _TCHAR* argv[])
{

	//TaskManager* pTaskMgr = TaskManager::Get();
	//CreateFileAction action;
	//pTaskMgr->RegisterAction(&action);

	//new CreateFileAction();
	//new FileExistsCondition();
	//new FileExistsCondition();

	//pTaskMgr->AddActionTask(new CreateFileAction());
	//pTaskMgr->AddActionTask(new CreateFileAction());


	//BrainUtil::MakeLink(_T("C:\\new FolderRoot\\new Folder\\Root\\"), _T("C:\\Root\\"));
	//BrainUtil::MakeLink(_T("C:\\new FolderRoot\\new Folder\\Root"), _T("C:\\Root\\"), false);
	//BrainUtil::MakeLink(_T("C:\\new FolderRoot\\new Folder\\reason\\remoteServer"), _T("\\\\shasrvms2\\Inventor\\BuildEnvironment"));
	//BrainUtil::MakeLink(_T("C:\\new FolderRoot\\new Folder\\test.txt"), _T("C:\\test.txt"), false);

	//BrainUtil::RunSystemCommand(_T("mklink /D \"C:\\new FolderRoot\\new Folder\\reason\\Root\" \"C:\\Root\""));

	//TestParameterObject();
	//TestFileExistsCondition();
	//TestFolderExistsCondition();

	//VariableManager::Get()->GetNextVariable(_T("1%a12356"));
	//Parameter var1(_T("AppPath"), _T("C:\\newFolder"));
	//Parameter var3(_T("AppPath"), _T("C:\\MyApp"));
	//Parameter var4(_T("DocName"), _T("%DocPath%\\help.txt"));
	//Parameter var2(_T("DocPath"), _T("%%%AppPath%\\d%%oc\\%Docname%\\%%%%"));
	//VariableManager::Get()->AddParameter(var1);
	//VariableManager::Get()->AddParameter(var2);
	//VariableManager::Get()->AddParameter(var3);
	//VariableManager::Get()->AddParameter(var4);

	//CString str = var2.GetEvaluatedValue();

	//BrainUtil::DoesFileorFolderExist(_T("C:\\"));
	//BrainUtil::DoesFileorFolderExist(_T("C:\\2"));
	//BrainUtil::DoesFileorFolderExist(_T("\\\\ss\\ff"));
	//BrainUtil::DoesFileorFolderExist(_T("\\\\shamsdfs01\\asdf\\"));

	//BrainUtil::CopyFile(_T("\\\\ff\\saf\\compile.log"), _T("C:\\pccompile.log"));
	//BrainUtil::CopyFile(_T("\\\\ss\\asf\\compile.log"), _T("C:\\newFolder\\childeFolder\\pccompile.log"));
	//BrainUtil::CopyFolder(_T("C:\\Perl64\\site\\"), _T("C:\\DestFolder\\"));
	//BrainUtil::CopyFolder(_T("C:\\Perl64\\site"), _T("C:\\DestFolder\\in\\one"));

	//BrainUtil::DeleteFolder(_T("C:\\DestFolder\\"));
	//BrainUtil::DeleteFile(_T("C:\\pccompile.log"));

	//BrainUtil::CreateFile(_T("C:\\new FolderRoot\\new Folder\\new File.txt"));
	return 0;
}

void TestFolderExistsCondition()
{
	Parameter para(FOLDER_NAME, _T("C:\\"));
	//Parameter para(_T("FolderName"), _T("C:\\tte"));
	FolderExistsCondition condition;
	condition.AddParameter(para);

	bool ret = condition.IsTrue();
}

void TestFileExistsCondition()
{
	Parameter para(FILE_NAME, _T("C:\\tte")); // Local file
	//Parameter para(_T("FileName"), _T("C:\\test.txt")); // Local file
	//Parameter para(_T("FileName"), _T("\\\\aaa\DM\txt.txt")); // network file
	FileExistsCondition condition;
	condition.AddParameter(para);

	bool ret = condition.IsTrue();
}

void TestParameterObject()
{
	Parameter fileNamePara(_T("FileName"), _T("C:\\test.txt"));
	ParameterObject paraObj;
	paraObj.AddParameter(fileNamePara);

	Parameter para;
	bool ret = paraObj.GetParameter(_T("FileName"), para); //

	Parameter fileNamePara2(_T("FileName"), _T("C:\\test2.txt"));
	fileNamePara2.SetComments(_T("second one"));

	paraObj.AddParameter(fileNamePara2);
	ret = paraObj.GetParameter(_T("FileName"), para);//

	ret = paraObj.GetParameter(_T("FileName2"), para);//
}


