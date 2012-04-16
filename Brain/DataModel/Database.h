#pragma once
#include "IDatabaseObject.h"

class BehaviorManager;
class VariableManager;
class TaskSystem;


class Database : public IDataBaseObject
{
public:
	Database(TaskSystem* pTaskSystem);
	~Database();

public:
	BehaviorManager*			GetBehaviorManager() const;
	VariableManager*		GetVariableManager() const;

public:
	virtual bool			XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool			XmlOut(XmlIOStream* pXmlIOStream) const;

private:
	TaskSystem*		m_pTaskSystem; // Back pointer

	BehaviorManager*			m_pBehaviorManager;
	VariableManager*		m_pVariableManager;
};

