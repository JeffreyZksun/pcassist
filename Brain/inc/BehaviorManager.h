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

typedef boost::shared_ptr<BehaviorNode>		BehaviorNodePtr;
typedef boost::shared_ptr<Action>			ActionPtr;
typedef boost::shared_ptr<Condition>		ConditionPtr;

//////////////////////////////////////////////////////////////////////////
// BehaviorManager
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT BehaviorManager : public IDataBaseObject
{
public:
    BehaviorManager(TaskSystem* pTaskSystem);
    ~BehaviorManager(void);

public:
    bool                    RegisterAction(ActionPtr);
    void                    UnregisterAction(ActionPtr);
	ActionPtr				GetActionById(const CString&) const;
	ActionPtr				GetActionByIndex(size_t index) const;
	size_t					GetActionCount() const;

    bool                    RegisterCondition(ConditionPtr);
    void                    UnregisterCondition(ConditionPtr);
	ConditionPtr				GetConditionById(const CString&) const;

    void                    AddActionTask(ActionPtr);
    void                    RemoveActionTask(ActionPtr);

    bool                    RunTasks();

	virtual bool			XmlIn(XmlIOStream* pXmlIOStream);
	virtual bool			XmlOut(XmlIOStream* pXmlIOStream) const;

	TaskSystem*				GetTaskSystem() const;

public:
    void                    deleteRegisteredActions();
    void                    deleteRegisteredConditions();

private:
	typedef std::list<BehaviorNodePtr>	BehaviorNodeList;
	typedef std::list<CString>			ActionList;

private:
	bool                    _RegisterBehaviorNode(BehaviorNodeList&, BehaviorNodePtr);
	void                    _UnregisterBehaviorNode(BehaviorNodeList&, BehaviorNodePtr);
	BehaviorNodePtr			_GetBehaviorNodeById(const BehaviorNodeList&, const CString&) const;
	void					_DeleteBehaviorNodes(BehaviorNodeList&);

private:

    BehaviorNodeList			mRegisteredActions;
    BehaviorNodeList			mRegisteredConditions;

    ActionList					mTaskList;

	TaskSystem*					mpTaskSystem; // Back-pointer

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
	BehaviorManager*GetBehaviorManager() const;

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
	typedef boost::shared_ptr<Action>		pointer;	

public:
    virtual ~Action(void);

	static pointer		Create();
	static pointer		Create(const CString& objetType, BehaviorManager* pBehaviorManager);

protected:
	Action();
    Action(const CString& objetType);

public:
    bool				Execute();
};


//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

class BRAINEXPORT Condition : public BehaviorNode
{
public:
	typedef boost::shared_ptr<Condition>		pointer;	

public:
    virtual ~Condition(void);

	static pointer		Create();
	static pointer		Create(const CString& objetType, BehaviorManager* pBehaviorManager);

protected:
	Condition();
	Condition(const CString& objetType);

public:
    bool				IsTrue();
};


#pragma warning( pop ) 
