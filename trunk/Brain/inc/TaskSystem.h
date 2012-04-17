#pragma once

#include "BrainSystem.h"
#include "ITaskSystem.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class BehaviorManager;
class BehaviorBodyFactory;
class VariableManager;
class IHostService;
class IOSProvider;
class Database;


class BRAINEXPORT TaskSystem : public ITaskSystem
{
public:
	TaskSystem();
	virtual ~TaskSystem();

public:
	// override ITaskSystem 
	virtual BehaviorManager*		GetBehaviorManager() const;
	virtual BehaviorBodyFactory*	GetBehaviorBodyFactory() const;
	virtual VariableManager*		GetVariableManager() const;
	virtual IOSProvider*			GetOSProvider() const;
	virtual Database*				GetDatabase() const;
	virtual Ts::ITaskManagerPtr		GetTaskManager() const;

public:
	bool		XmlIn(const CString& docName) const;
	bool		XmlOut(const CString& docName) const;

private:
	void		Initialize();

private:
	Database*				m_pDatabase;
	BehaviorBodyFactory*	mpBehaviorBodyFactory;
	IHostService*			mpHostService;
	Ts::ITaskManagerPtr		m_pTaskManager;
};

#pragma warning( pop ) 
