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
#include "DocumentManager.h"

void TestFileExistsCondition();
void TestParameterObject();
void TestFolderExistsCondition();

int _tmain(int argc, _TCHAR* argv[])
{

	////////////////// Test DocumentManager
	//DocumentManager* pDoc = new DocumentManager();
	//pDoc->SetDocumentName(_T("C:\\My.xml"));
	//pDoc->XmlOut();
	//delete pDoc;

	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(_T("C:\\My.xml"));
	pDoc->XmlOut();
	delete pDoc;
	/////////////////////////////////////////////////// Test ComplexAction
	//Condition* pC  = new FileExistsCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CheckFolder")));
	//pC->AddParameter(Parameter(FILE_NAME, _T("C:\\temp")));

	//Action* pPreAction = new CreateFolderAction();
	//pPreAction->AddParameter(Parameter(OBJECT_ID, _T("PreAction")));
	//pPreAction->AddParameter(Parameter(FOLDER_NAME, _T("C:\\temp\\preaction")));

	//Action* pMainAction = new CreateFolderAction();
	//pMainAction->AddParameter(Parameter(OBJECT_ID, _T("MainAction")));
	//pMainAction->AddParameter(Parameter(FOLDER_NAME, _T("C:\\temp\\mainaction")));

	//Action* pPostAction = new CreateFolderAction();
	//pPostAction->AddParameter(Parameter(OBJECT_ID, _T("PostAction")));
	//pPostAction->AddParameter(Parameter(FOLDER_NAME, _T("C:\\temp\\postaction")));

	//Action* pComplexAction = new ComplexAction();
	//pComplexAction->AddParameter(Parameter(OBJECT_ID, _T("CreateFolders")));
	//pComplexAction->AddParameter(Parameter(EXECUTE_CONDITION, _T("CheckFolder")));
	//pComplexAction->AddParameter(Parameter(PRE_ACTION, _T("PreAction")));
	//pComplexAction->AddParameter(Parameter(MAIN_ACTION, _T("MainAction")));
	//pComplexAction->AddParameter(Parameter(POST_ACTION, _T("PostAction")));

	//Action* pA = TaskManager::Get()->GetActionById(_T("CreateFolders"));

	//bool bRet = pA->Execute();

	//int i =10;

	/////////////////////////////////////// Test ComplexAction close loop reference A<-->B
	//Condition* pC  = new FileExistsCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CheckFolder")));
	//pC->AddParameter(Parameter(FILE_NAME, _T("C:\\temp")));

	//Action* pActionA = new ComplexAction();
	//pActionA->AddParameter(Parameter(OBJECT_ID, _T("A")));
	//pActionA->AddParameter(Parameter(EXECUTE_CONDITION, _T("CheckFolder")));
	//pActionA->AddParameter(Parameter(PRE_ACTION, _T("PreAction")));
	//pActionA->AddParameter(Parameter(MAIN_ACTION, _T("B")));
	//pActionA->AddParameter(Parameter(POST_ACTION, _T("PostAction")));

	//Action* pActionB = new ComplexAction();
	//pActionB->AddParameter(Parameter(OBJECT_ID, _T("B")));
	//pActionB->AddParameter(Parameter(EXECUTE_CONDITION, _T("CheckFolder")));
	//pActionB->AddParameter(Parameter(PRE_ACTION, _T("PreAction")));
	//pActionB->AddParameter(Parameter(MAIN_ACTION, _T("A")));
	//pActionB->AddParameter(Parameter(POST_ACTION, _T("PostAction")));


	//bool bRet = pActionA->Execute();

	/////////////////////////////////////// Test ComplexCondition
	//Condition* pC  = new FileExistsCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CheckDiskC")));
	//pC->AddParameter(Parameter(FILE_NAME, _T("C:\\")));

	//pC = new FileExistsCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CheckDiskAZ")));
	//pC->AddParameter(Parameter(FILE_NAME, _T("AZ:\\")));

	//pC = new ComplexCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CheckDiskCD")));
	//pC->AddParameter(Parameter(BOOL_OPERATOR, _T("OR")));
	//pC->AddParameter(Parameter(FIRST_CONDITION, _T("CheckDiskC")));
	//pC->AddParameter(Parameter(SECOND_CONDITION, _T("CheckDiskAZ")));

	//Condition* pC2 = TaskManager::Get()->GetConditionById(_T("CheckDiskCD"));
	//bool bIsTrue = pC2->IsTrue();


	/////////////////////////////////////// Test ComplexCondition close loop reference A<-->B
	//Condition* pCA = new ComplexCondition();
	//pCA->AddParameter(Parameter(OBJECT_ID, _T("CA")));
	//pCA->AddParameter(Parameter(BOOL_OPERATOR, _T("Not")));
	//pCA->AddParameter(Parameter(FIRST_CONDITION, _T("CB")));

	//Condition* pCB = new ComplexCondition();
	////pCB->AddParameter(Parameter(OBJECT_ID, _T("CA")));
	//pCB->AddParameter(Parameter(OBJECT_ID, _T("CB")));
	//pCB->AddParameter(Parameter(BOOL_OPERATOR, _T("Not")));
	//pCB->AddParameter(Parameter(FIRST_CONDITION, _T("CA")));

	//bool bIsTrue = pCB->IsTrue();

	///////////////////////////////////////////// Test GetActionById, GetConditionById
	//TaskManager* pTaskMgr = TaskManager::Get();
	//new CreateFileAction();
	//Action* pA = new CreateFileAction();
	//pA->AddParameter(Parameter(OBJECT_ID, _T("CreateOS")));

	//Action* pA2 = TaskManager::Get()->GetActionById(_T("CreateOS"));

	//new FileExistsCondition();
	//Condition* pC = new FileExistsCondition();
	//pC->AddParameter(Parameter(OBJECT_ID, _T("CreateOS")));

	//Condition* pC2 = TaskManager::Get()->GetConditionById(_T("CreateOS"));

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

	//////////////////////////////////////////Test dead loop
	//Parameter var1(_T("AppPath"), _T("%ExePath%"));
	//Parameter var2(_T("ExePath"), _T("C:\\%AppPath%"));

	//VariableManager::Get()->AddParameter(var1);
	//VariableManager::Get()->AddParameter(var2);

	//var2.GetEvaluatedValue();

	////////////////////////////////////////Test correct parser
	//Parameter var1(_T("AppPath"), _T("%ExePath%"));
	//Parameter var2(_T("ExePath"), _T("%ProgramFile%\\MyApp"));
	//Parameter var3(_T("ProgramFile"), _T("C:\\Program Files"));

	//VariableManager::Get()->AddParameter(var1);
	//VariableManager::Get()->AddParameter(var2);
	//VariableManager::Get()->AddParameter(var3);

	//CString str = var1.GetEvaluatedValue();

	//int i = 10;

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


