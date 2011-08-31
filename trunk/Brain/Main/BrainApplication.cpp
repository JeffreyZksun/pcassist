#include "StdAfx.h"
#include "BrainApplication.h"
#include "TaskManager.h"
#include "BehaviorNodeFactory.h"
#include "VariableManager.h"
#include "DocumentManager.h"


BrainApplication::BrainApplication()
		: mpTaskManager(new TaskManager())
		, mpBehaviorNodeFactory(new BehaviorNodeFactory())
		, mpVariableManager(new VariableManager())
{

}

BrainApplication::~BrainApplication()
{
	delete mpTaskManager;
	delete mpBehaviorNodeFactory;
	delete mpVariableManager;
}
static bool bInitialized = false;

BrainApplication* BrainApplication::GetWorkingBrain()
{
	static BrainApplication singleton;
	if(!bInitialized)
	{
		bInitialized = true;
		singleton.Initialize();
	}
	return &singleton;
}

TaskManager* BrainApplication::GetTaskManager() const
{
	return mpTaskManager;
}

BehaviorNodeFactory* BrainApplication::GetBehaviorNodeFactory() const
{
	return mpBehaviorNodeFactory;
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

void BrainApplication::Initialize() const
{
	AddBuiltInActionBehaivor();
	AddBuiltInConditionBehaivor();
}
