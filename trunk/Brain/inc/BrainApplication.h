#pragma once
#include <atlstr.h> // CString
#include "BrainSystem.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class TaskManager;
class BehaviorNodeFactory;
class VariableManager;

class BRAINEXPORT BrainApplication
{
public:
	BrainApplication();
	~BrainApplication();

public:
	TaskManager*			GetTaskManager() const;
	BehaviorNodeFactory*	GetBehaviorNodeFactory() const;
	VariableManager*		GetVariableManager() const;
	static BrainApplication* GetWorkingBrain();

public:
	bool		XmlIn(const CString& docName) const;
	bool		XmlOut(const CString& docName) const;

private:
	void		Initialize() const;

	// We can combain the two functions together.
	void		AddBuiltInActionBehaivor() const; // Defined in Action.cpp
	void		AddBuiltInConditionBehaivor() const; // Defined in Condition.cpp

private:
	TaskManager*			mpTaskManager;
	BehaviorNodeFactory*	mpBehaviorNodeFactory;
	VariableManager*		mpVariableManager;
};

#pragma warning( pop ) 
