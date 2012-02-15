#pragma once
#include <atlstr.h> // CString
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

class BRAINEXPORT BrainApplication
{
public:
	BrainApplication();
	~BrainApplication();

public:
	TaskManager*			GetTaskManager() const;
	BehaviorBodyFactory*	GetBehaviorBodyFactory() const;
	VariableManager*		GetVariableManager() const;
	IOSProvider*			GetOSProvider() const;


public:
	// singleton
	static BrainApplication* GetWorkingBrain();
	static BrainApplication* SetWorkingBrain(BrainApplication*);

public:
	bool		XmlIn(const CString& docName) const;
	bool		XmlOut(const CString& docName) const;

private:
	void		Initialize();


private:
	TaskManager*			mpTaskManager;
	BehaviorBodyFactory*	mpBehaviorBodyFactory;
	VariableManager*		mpVariableManager;
	IHostService*			mpHostService;

};

#pragma warning( pop ) 
