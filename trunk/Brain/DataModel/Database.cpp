#include "StdAfx.h"
#include "Database.h"
#include "BehaviorManager.h"
#include "VariableManager.h"
#include "TaskSystem.h"

Database::Database(TaskSystem* pTaskSystem)
		: m_pTaskSystem(pTaskSystem)
		, m_pBehaviorManager(new BehaviorManager(pTaskSystem))
		, m_pVariableManager(new VariableManager(pTaskSystem->GetOSProvider()))
{
}

Database::~Database()
{
	// Do nothing to m_pTaskSystem;
	delete m_pBehaviorManager;
	delete m_pVariableManager;
}

BehaviorManager* Database::GetBehaviorManager() const
{
	return m_pBehaviorManager;
}

VariableManager* Database::GetVariableManager() const
{
	return m_pVariableManager;
}

bool Database::XmlIn(XmlIOStream* pXmlIOStream) 
{
	// Load variable manager
	bool bRet = m_pVariableManager->XmlIn(pXmlIOStream);

	// Load task manager
	bRet = m_pBehaviorManager->XmlIn(pXmlIOStream);

	return bRet;
}

bool Database::XmlOut(XmlIOStream* pXmlIOStream) const
{
	// Load variable manager
	bool bRet = m_pVariableManager->XmlOut(pXmlIOStream);

	// Load task manager
	bRet = m_pBehaviorManager->XmlOut(pXmlIOStream);

	return bRet;
}
