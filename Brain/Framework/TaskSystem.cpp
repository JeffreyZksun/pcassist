#include "StdAfx.h"
#include "TaskSystem.h"
#include "BehaviorBodyFactory.h"
#include "DocumentManager.h"

#include "HostService.h"
#include "IBehaviorBuilder.h"
#include "Database.h"


TaskSystem::TaskSystem()
		: mpBehaviorBodyFactory(new BehaviorBodyFactory())
		, mpHostService(new HostService()) // ToDo - This data should be set by client.
		, m_pDatabase(NULL)
{
	m_pDatabase = new Database(this); // IMPORTANT: This object must be constructed after mpHostService.
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
