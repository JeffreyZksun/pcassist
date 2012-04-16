#pragma once

#include <list>
#include "ParameterTable.h"
#include "IDataBaseObject.h"

#pragma warning( push )
// http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
//Disable the waring " class 'ATL::CStringT<BaseType,StringTraits>' needs to have dll-interface to be used by clients of class"
#pragma warning( disable : 4251 ) 

class BehaviorNode;
class Action;
class Condition;
class XmlIOStream;
class TaskSystem;

//////////////////////////////////////////////////////////////////////////
// BehaviorManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT BehaviorManager : IDataBaseObject
{
public:
    BehaviorManager(TaskSystem* pTaskSystem);
    ~BehaviorManager(void);

public:
    bool                    RegisterAction(Action*);
    void                    UnregisterAction(Action*);
	Action*					GetActionById(const CString&) const;
	Action*					GetActionByIndex(size_t index) const;
	size_t					GetActionCount() const;

    bool                    RegisterCondition(Condition*);
    void                    UnregisterCondition(Condition*);
	Condition*				GetConditionById(const CString&) const;

    void                    AddActionTask(Action*);
    void                    RemoveActionTask(Action*);

    bool                    RunTasks();

	virtual bool			XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool			XmlOut(XmlIOStream* pXmlIOStream) const;

	TaskSystem*		GetTaskSystem() const;

public:
    void                    deleteRegisteredActions();
    void                    deleteRegisteredConditions();

private:
	typedef std::list<BehaviorNode*>	BehaviorNodeList;
	typedef std::list<CString>			ActionList;

private:
	bool                    _RegisterBehaviorNode(BehaviorNodeList&, BehaviorNode*);
	void                    _UnregisterBehaviorNode(BehaviorNodeList&, BehaviorNode*);
	BehaviorNode*			_GetBehaviorNodeById(const BehaviorNodeList&, const CString&) const;
	void					_DeleteBehaviorNodes(BehaviorNodeList&);

private:

    BehaviorNodeList			mRegisteredActions;
    BehaviorNodeList			mRegisteredConditions;

    ActionList					mTaskList;

	TaskSystem*			mpTaskSystem; // Back-pointer

};

//////////////////////////////////////////////////////////////////////////
// BehaviorNode
// The base class for the action and condition.
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT BehaviorNode : IDataBaseObject
{
public:
	BehaviorNode();
	BehaviorNode(const CString& objetType);
	virtual ~BehaviorNode();

	CString			GetObjectId() const;
	CString			GetObjectType() const;

	void			SetBehaviorManager(BehaviorManager* pBehaviorManager);
	BehaviorManager*	GetBehaviorManager() const;

	ParameterTable& GetParameterTable();

	virtual bool	XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool	XmlOut(XmlIOStream* pXmlIOStream) const;

protected:
	bool			ExecuteBehavior();

private:
	BehaviorManager*	mpBehaviorManager; // This pointer is set when it is added to the task manager.
	ParameterTable	mParameterTable;

	bool			mbIsExecuting; // Don't persist. Used for reference loop check.
};

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Action : public BehaviorNode
{
public:
	Action();
	//Action(const CString& objetType);
    Action(BehaviorManager* pBehaviorManager, const CString& objetType);
    virtual ~Action(void);

protected:
	//virtual bool		IsParameterValid(const Parameter& para) const;

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
    //Condition(const CString& objetType);
	Condition(BehaviorManager* pBehaviorManager, const CString& objetType);
    virtual ~Condition(void);

protected:
	//virtual bool		IsParameterValid(const Parameter& para) const;

public:
    bool				IsTrue();
};


#pragma warning( pop ) 
