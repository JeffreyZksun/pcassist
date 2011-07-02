#include "StdAfx.h"
#include "BehaviorNodeFactory.h"
#include "BrainApplication.h"

BehaviorNodeFactory::BehaviorNodeFactory(void) : mBehaviorFunctionMap()
{
	mBehaviorFunctionMap.clear();
}

BehaviorNodeFactory::~BehaviorNodeFactory(void)
{
	mBehaviorFunctionMap.clear();
}

BehaviorFunction BehaviorNodeFactory::GetBehaviorFunction(const CString& objectType) const
{
	CString objType = objectType;
	objType.MakeLower();

	FunctionMap::const_iterator it = mBehaviorFunctionMap.find(objType);
	
	if(it != mBehaviorFunctionMap.end())
		return it->second;

	return NULL;
}

void BehaviorNodeFactory::AddBehaviorFunction(const CString& objectType, BehaviorFunction pFunction)
{
	CString objType = objectType;
	objType.MakeLower();

	FunctionMap::iterator it = mBehaviorFunctionMap.find(objType);
	ASSERT(mBehaviorFunctionMap.end() == it); // Check duplication.
	if(mBehaviorFunctionMap.end() == it)
		mBehaviorFunctionMap.insert(std::make_pair(objType, pFunction));
}

void BehaviorNodeFactory::RemoveBehaviorFunction(const CString& objectType)
{
	CString objType = objectType;
	objType.MakeLower();

	FunctionMap::iterator it = mBehaviorFunctionMap.find(objType);
	if(it != mBehaviorFunctionMap.end())
		mBehaviorFunctionMap.erase(it);
}

//BehaviorNodeFactory* BrainApplication::GetWorkingBrain()->GetBehaviorNodeFactory()
//{
//	static BehaviorNodeFactory singleton;
//	return &singleton;
//}
//
//BehaviorFunctionHelper::BehaviorFunctionHelper(const CString& objectType, BehaviorFunction pFunction) 
//	: mObjectType(objectType)
//{
//	BrainApplication::GetWorkingBrain()->GetBehaviorNodeFactory()->AddBehaviorFunction(objectType, pFunction);
//}
//
//BehaviorFunctionHelper::~BehaviorFunctionHelper(void)
//{
//	BrainApplication::GetWorkingBrain()->GetBehaviorNodeFactory()->RemoveBehaviorFunction(mObjectType);
//}