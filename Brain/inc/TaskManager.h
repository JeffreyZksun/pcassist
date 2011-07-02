#pragma once

#include <list>
#include "ParameterObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class BehaviorNode;
class Action;
class Condition;
class XmlIOStream;

//////////////////////////////////////////////////////////////////////////
// TaskManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT TaskManager
{
public:
    TaskManager(void);
    ~TaskManager(void);

    //static TaskManager*     Get();

public:
    bool                    RegisterAction(Action*);
    void                    UnregisterAction(Action*);
	Action*					GetActionById(const CString&) const;

    bool                    RegisterCondition(Condition*);
    void                    UnregisterCondition(Condition*);
	Condition*				GetConditionById(const CString&) const;

    void                    AddActionTask(Action*);
    void                    RemoveActionTask(Action*);

    bool                    RunTasks();

	bool					XmlIn(XmlIOStream* pXmlIOStream);
	bool					XmlOut(XmlIOStream* pXmlIOStream) const;

private:
    void                    deleteRegisteredActions();
    void                    deleteRegisteredConditions();

private:
	typedef std::list<BehaviorNode*>	BehaviorNodeList;
	typedef std::list<Action*>			ActionList;

private:
	bool                    _RegisterBehaviorNode(BehaviorNodeList&, BehaviorNode*);
	void                    _UnregisterBehaviorNode(BehaviorNodeList&, BehaviorNode*);
	BehaviorNode*			_GetBehaviorNodeById(const BehaviorNodeList&, const CString&) const;
	void					_DeleteBehaviorNodes(BehaviorNodeList&);

private:

    BehaviorNodeList			mRegisteredActions;
    BehaviorNodeList			mRegisteredContions;

    ActionList					mTaskList;

};

//////////////////////////////////////////////////////////////////////////
// BehaviorNode
// The base class for the action and condition.
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT BehaviorNode : public ParameterObject
{
public:
	BehaviorNode();
	BehaviorNode(const CString& objetType);

	CString			GetObjectId() const;
	CString			GetObjectType() const;

protected:
	bool			ExecuteBehavior();
};

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Action : public BehaviorNode
{
public:
	Action();
    Action(const CString& objetType);
    virtual ~Action(void);

protected:
	virtual bool		IsParameterValid(const Parameter& para) const;

public:
    bool				Execute();
};


//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Condition : public BehaviorNode
{
public:
	Condition();
    Condition(const CString& objetType);
    virtual ~Condition(void);

protected:
	virtual bool		IsParameterValid(const Parameter& para) const;

public:
    bool				IsTrue();
};

#pragma warning( pop ) 
