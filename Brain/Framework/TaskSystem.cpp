#include "StdAfx.h"
#include "TaskSystem.h"
#include "BehaviorBodyFactory.h"
#include "DocumentManager.h"

#include "HostService.h"
#include "IBehaviorBuilder.h"
#include "Database.h"
#include "TaskManager.h"


TaskSystem::TaskSystem()
		: mpBehaviorBodyFactory(new BehaviorBodyFactory())
		, mpHostService(new HostService()) // ToDo - This data should be set by client.
		, m_pDatabase(NULL)
		, m_pTaskManager()
{
	m_pDatabase = new Database(this); // IMPORTANT: This object must be constructed after mpHostService.
	m_pTaskManager = Ts::TaskManager::Create(this);
	Initialize();
}

TaskSystem::~TaskSystem()
{
	delete m_pDatabase;
	delete mpBehaviorBodyFactory;
}

BehaviorManager* TaskSystem::GetBehaviorManager() const
{
	return m_pDatabase->GetBehaviorManager();
}

BehaviorBodyFactory* TaskSystem::GetBehaviorBodyFactory() const
{
	return mpBehaviorBodyFactory;
}

VariableManager* TaskSystem::GetVariableManager() const
{
	return m_pDatabase->GetVariableManager();
}

IOSProvider* TaskSystem::GetOSProvider() const
{
	if(mpHostService)
	{
		return mpHostService->GetOSProvider();
	}

	return NULL;
}

Database* TaskSystem::GetDatabase() const
{
	return m_pDatabase;
}

Ts::ITaskManagerPtr TaskSystem::GetTaskManager() const
{
	return m_pTaskManager;
}

bool TaskSystem::XmlIn(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlIn(m_pDatabase);

	return bRet;
}

bool TaskSystem::XmlOut(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlOut(m_pDatabase);

	return bRet;
}

void TaskSystem::Initialize()
{
	ASSERT(mpHostService != NULL);
	if(mpHostService)
	{
		IBehaviorBuilder* pBuilder = mpHostService->GetBehaviorBuilder();
		ASSERT(pBuilder != NULL);
		if(pBuilder)
			pBuilder->InitializeBehaviorBodyFactory(GetBehaviorBodyFactory());
	}
}
