#include "StdAfx.h"
#include "BrainApplication.h"
#include "TaskManager.h"
#include "BehaviorBodyFactory.h"
#include "VariableManager.h"
#include "DocumentManager.h"
#include "Actions.h"
#include "Conditions.h"


BrainApplication::BrainApplication()
		: mpTaskManager(new TaskManager())
		, mpBehaviorBodyFactory(new BehaviorBodyFactory())
		, mpVariableManager(new VariableManager())
{
	Initialize();
}

BrainApplication::~BrainApplication()
{
	delete mpTaskManager;
	delete mpBehaviorBodyFactory;
	delete mpVariableManager;
}


static BrainApplication	defaultApp;
static BrainApplication* pCurrentApp = &defaultApp;

BrainApplication* BrainApplication::GetWorkingBrain()
{
	return pCurrentApp;
}

BrainApplication* BrainApplication::SetWorkingBrain(BrainApplication* pNewApp)
{
	ASSERT(pNewApp != NULL);
	if(NULL == pNewApp) 
		return NULL;

	BrainApplication* pPreviousApp = pCurrentApp;
	pCurrentApp = pNewApp;
	return pPreviousApp;
}

TaskManager* BrainApplication::GetTaskManager() const
{
	return mpTaskManager;
}

BehaviorBodyFactory* BrainApplication::GetBehaviorBodyFactory() const
{
	return mpBehaviorBodyFactory;
}

VariableManager* BrainApplication::GetVariableManager() const
{
	return mpVariableManager;
}

bool BrainApplication::XmlIn(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlIn(this);

	return bRet;
}

bool BrainApplication::XmlOut(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlOut(this);

	return bRet;
}

void BrainApplication::Initialize()
{
	AddBuiltInActionBehaivor();
	AddBuiltInConditionBehaivor();
}

#define ADD_BEHAVIORBODY_TO_FACTORY(BehaviorName) \
	this->GetBehaviorBodyFactory()->AddBehaviorBody(_T(#BehaviorName), new BehaviorName());

void BrainApplication::AddBuiltInConditionBehaivor() const
{
	ADD_BEHAVIORBODY_TO_FACTORY(CompositeCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(FileExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(FolderExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(RegisterKeyExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(ProcessRunningCondition);
}


void BrainApplication::AddBuiltInActionBehaivor() const
{
	ADD_BEHAVIORBODY_TO_FACTORY(ComplexAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CreateFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(DeleteFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CopyFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CreateFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(DeleteFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CopyFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(MakeDirectoryLinkAction);
	ADD_BEHAVIORBODY_TO_FACTORY(RunSystemCommandAction);
	ADD_BEHAVIORBODY_TO_FACTORY(RunProcessAction);
	ADD_BEHAVIORBODY_TO_FACTORY(ConditionBlockAction);
}

