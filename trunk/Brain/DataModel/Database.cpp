#include "StdAfx.h"
#include "Database.h"
#include "TaskManager.h"
#include "VariableManager.h"
#include "BrainApplication.h"

Database::Database(BrainApplication* pBrainApplication)
		: m_pBrainApplication(pBrainApplication)
		, m_pTaskManager(new TaskManager(pBrainApplication))
		, m_pVariableManager(new VariableManager(pBrainApplication->GetOSProvider()))
{
}

Database::~Database()
{
	// Do nothing to m_pBrainApplication;
	delete m_pTaskManager;
	delete m_pVariableManager;
}


TaskManager* Database::GetTaskManager() const
{
	return m_pTaskManager;
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
	bRet = m_pTaskManager->XmlIn(pXmlIOStream);

	return bRet;
}

bool Database::XmlOut(XmlIOStream* pXmlIOStream) const
{
	// Load variable manager
	bool bRet = m_pVariableManager->XmlOut(pXmlIOStream);

	// Load task manager
	bRet = m_pTaskManager->XmlOut(pXmlIOStream);

	return bRet;
}
