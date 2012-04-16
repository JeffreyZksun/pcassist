#pragma once
#include "IDatabaseObject.h"

class TaskManager;
class VariableManager;
class TaskSystem;


class Database : public IDataBaseObject
{
public:
	Database(TaskSystem* pTaskSystem);
	~Database();

public:
	TaskManager*			GetTaskManager() const;
	VariableManager*		GetVariableManager() const;

public:
	virtual bool			XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool			XmlOut(XmlIOStream* pXmlIOStream) const;

private:
	TaskSystem*		m_pTaskSystem; // Back pointer

	TaskManager*			m_pTaskManager;
	VariableManager*		m_pVariableManager;
};

