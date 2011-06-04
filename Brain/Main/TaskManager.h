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

    void                    RegisterCondition(Condition*);
    void                    UnregisterCondition(Condition*);

    void                    AddActionTask(Action*);
    void                    RemoveActionTask(Action*);

    bool                    RunTasks();

private:
    void                    deleteRegisteredActions();
    void                    deleteRegisteredConditions();

    typedef std::list<Action*>      ActionList;
    typedef std::list<Condition*>   ConditionList;
private:
    ActionList              mRegisteredActions;
    ConditionList           mRegisteredContions;

    ActionList              mTaskList;

};

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Action : public ParameterObject
{
public:
    Action(void);
    virtual ~Action(void);

public:
    virtual bool Execute() = 0;
};


//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Condition : public ParameterObject
{
public:
    Condition(void);
    virtual ~Condition(void);

public:
    virtual bool IsTrue() = 0;
};

#pragma warning( pop ) 
