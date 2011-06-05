#include "StdAfx.h"
#include "BehaviorNodeFactory.h"

BehaviorNodeFactory::BehaviorNodeFactory(void) : mCreationFunctionMap()
{
}

BehaviorNodeFactory::~BehaviorNodeFactory(void)
{
	mCreationFunctionMap.clear();
}

BehaviorNode* BehaviorNodeFactory::CreteBehaviorNodeByType(const CString& objectType) const
{
	FunctionMap::const_iterator it = mCreationFunctionMap.find(objectType);
	
	if(it != mCreationFunctionMap.end())
		return (it->second)();

	return NULL;
}

void BehaviorNodeFactory::AddCreationFunction(const CString& objectType, CreateBehaviorNode pFunction)
{
	FunctionMap::iterator it = mCreationFunctionMap.find(objectType);
	ASSERT(mCreationFunctionMap.end() == it); // Check duplication.
	if(mCreationFunctionMap.end() == it)
		mCreationFunctionMap.insert(std::make_pair(objectType, pFunction));
}

void BehaviorNodeFactory::RemoveCreationFunction(const CString& objectType)
{
	FunctionMap::iterator it = mCreationFunctionMap.find(objectType);
	if(it != mCreationFunctionMap.end())
		mCreationFunctionMap.erase(it);
}

BehaviorNodeFactory* BehaviorNodeFactory::Get()
{
	static BehaviorNodeFactory singleton;
	return &singleton;
}

BehaviorNodeCreationHelper::BehaviorNodeCreationHelper(const CString& objectType, CreateBehaviorNode pFunction) 
	: mObjectType(objectType)
{
	BehaviorNodeFactory::Get()->AddCreationFunction(objectType, pFunction);
}

BehaviorNodeCreationHelper::~BehaviorNodeCreationHelper(void)
{
	BehaviorNodeFactory::Get()->RemoveCreationFunction(mObjectType);
}