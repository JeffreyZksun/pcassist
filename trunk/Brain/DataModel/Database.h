#pragma once
#include "IDatabaseObject.h"

class TaskManager;
class VariableManager;
class BrainApplication;


class Database : public IDataBaseObject
{
public:
	Database(BrainApplication* pBrainApplication);
	~Database();

public:
	TaskManager*			GetTaskManager() const;
	VariableManager*		GetVariableManager() const;

public:
	virtual bool			XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool			XmlOut(XmlIOStream* pXmlIOStream) const;

private:
	BrainApplication*		m_pBrainApplication; // Back pointer

	TaskManager*			m_pTaskManager;
	VariableManager*		m_pVariableManager;
};

