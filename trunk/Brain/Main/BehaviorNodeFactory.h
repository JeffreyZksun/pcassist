#pragma once
#include <map>

class BehaviorNode;

// Define the creation function pointer
typedef bool (*BehaviorFunction)(BehaviorNode*);


#define BEHAVIOR_FUNCTION_IMP(BehaviorName) \
	bool BehaviorName(BehaviorNode* pSelf);\
	BehaviorFunctionHelper g##BehaviorName(_T(#BehaviorName), BehaviorName);\
	bool BehaviorName(BehaviorNode* pSelf)


class BehaviorNodeFactory
{
public:
	BehaviorNodeFactory(void);
	~BehaviorNodeFactory(void);

	BehaviorFunction	GetBehaviorFunction(const CString& objectType) const;
	void				AddBehaviorFunction(const CString& objectType, BehaviorFunction pFunction);
	void				RemoveBehaviorFunction(const CString& objectType);

	//static BehaviorNodeFactory* Get();

private:
	typedef std::map<CString, BehaviorFunction> FunctionMap;

	FunctionMap			mBehaviorFunctionMap;
};

class BehaviorFunctionHelper
{
public:
	BehaviorFunctionHelper(const CString& objectType, BehaviorFunction pFunction);
	~BehaviorFunctionHelper(void);

private:
	CString				mObjectType;
};
