#pragma once

#include "BrainSystem.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class TaskManager;
class BehaviorBodyFactory;
class VariableManager;
class IHostService;
class IOSProvider;
class Database;

class BRAINEXPORT TaskSystem
{
public:
	TaskSystem();
	~TaskSystem();

public:
	TaskManager*			GetTaskManager() const;
	BehaviorBodyFactory*	GetBehaviorBodyFactory() const;
	VariableManager*		GetVariableManager() const;
	IOSProvider*			GetOSProvider() const;
	Database*				GetDatabase() const;

public:
	bool		XmlIn(const CString& docName) const;
	bool		XmlOut(const CString& docName) const;

private:
	void		Initialize();

private:
	Database*				m_pDatabase;
	BehaviorBodyFactory*	mpBehaviorBodyFactory;
	IHostService*			mpHostService;

};

#pragma warning( pop ) 
