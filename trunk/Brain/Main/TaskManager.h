#pragma once

#include <list>
#include "ParameterObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class Action;
class Condition;

//////////////////////////////////////////////////////////////////////////
// TaskManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT TaskManager
{
public:
    TaskManager(void);
    ~TaskManager(void);

    static TaskManager*     Get();

public:
    void                    RegisterAction(Action*);
    void                    UnregisterAction(Action*);
	Action*					GetActionById(const CString& objectID) const;

    void                    RegisterCondition(Condition*);
    void                    UnregisterCondition(Condition*);
	Condition*				GetConditionById(const CString& objectID) const;

    void                    AddActionTask(Action*);
    void                    RemoveActionTask(Action*);

    bool                    RunTasks();

private:
    void                    deleteRegisteredActions();
    void                    deleteRegisteredConditions();

    typedef std::list<Action*>      ActionList;
    typedef std::list<Condition*>   ConditionList;
private:
	// ToDo - we can use the BehaviorNode list to avoid duplication.
    ActionList              mRegisteredActions;
    ConditionList           mRegisteredContions;

    ActionList              mTaskList;

};

//////////////////////////////////////////////////////////////////////////
// BehaviorNode
// The base class for the action and condition.
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT BehaviorNode : public ParameterObject
{
public:
	BehaviorNode(const CString& objetType);

	CString			GetObjectId() const;
	CString			GetObjectType() const;
};

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Action : public BehaviorNode
{
public:
    Action(const CString& objetType);
    virtual ~Action(void);

public:
    virtual bool Execute() = 0;
};


//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Condition : public BehaviorNode
{
public:
    Condition(const CString& objetType);
    virtual ~Condition(void);

public:
    virtual bool IsTrue() = 0;
};

#pragma warning( pop ) 
