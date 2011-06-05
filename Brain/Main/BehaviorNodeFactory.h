#pragma once
#include <map>

class BehaviorNode;

// Define the creation function pointer
typedef BehaviorNode* (*CreateBehaviorNode)();

class BehaviorNodeFactory
{
public:
	BehaviorNodeFactory(void);
	~BehaviorNodeFactory(void);

	BehaviorNode*	CreteBehaviorNodeByType(const CString& objectType) const;
	void			AddCreationFunction(const CString& objectType, CreateBehaviorNode pFunction);
	void			RemoveCreationFunction(const CString& objectType);

	static BehaviorNodeFactory* Get();

private:
	typedef std::map<CString, CreateBehaviorNode> FunctionMap;
	FunctionMap mCreationFunctionMap;
};

class BehaviorNodeCreationHelper
{
public:
	BehaviorNodeCreationHelper(const CString& objectType, CreateBehaviorNode pFunction);
	~BehaviorNodeCreationHelper(void);

private:
	CString		mObjectType;
};
