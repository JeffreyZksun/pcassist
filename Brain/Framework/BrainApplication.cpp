#include "StdAfx.h"
#include "BrainApplication.h"
#include "BehaviorBodyFactory.h"
#include "DocumentManager.h"

#include "HostService.h"
#include "IBehaviorBuilder.h"
#include "Database.h"


BrainApplication::BrainApplication()
		: mpBehaviorBodyFactory(new BehaviorBodyFactory())
		, mpHostService(new HostService()) // ToDo - This data should be set by client.
		, m_pDatabase(NULL)
{
	m_pDatabase = new Database(this); // IMPORTANT: This object must be constructed after mpHostService.
	Initialize();
}

BrainApplication::~BrainApplication()
{
	delete m_pDatabase;
	delete mpBehaviorBodyFactory;
}

TaskManager* BrainApplication::GetTaskManager() const
{
	return m_pDatabase->GetTaskManager();
}

BehaviorBodyFactory* BrainApplication::GetBehaviorBodyFactory() const
{
	return mpBehaviorBodyFactory;
}

VariableManager* BrainApplication::GetVariableManager() const
{
	return m_pDatabase->GetVariableManager();
}

IOSProvider* BrainApplication::GetOSProvider() const
{
	if(mpHostService)
	{
		return mpHostService->GetOSProvider();
	}

	return NULL;
}

Database* BrainApplication::GetDatabase() const
{
	return m_pDatabase;
}

bool BrainApplication::XmlIn(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlIn(m_pDatabase);

	return bRet;
}

bool BrainApplication::XmlOut(const CString& docName) const
{
	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(docName);
	bool bRet = pDoc->XmlOut(m_pDatabase);

	return bRet;
}

void BrainApplication::Initialize()
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