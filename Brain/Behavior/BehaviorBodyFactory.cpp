#include "StdAfx.h"
#include "BehaviorBodyFactory.h"
#include "TaskSystem.h"
#include "IBehaviorBody.h"

BehaviorBodyFactory::BehaviorBodyFactory(void) : mBehaviorBodyMap()
{
	//mBehaviorBodyMap.clear();
}

BehaviorBodyFactory::~BehaviorBodyFactory(void)
{
	for(BehaviorBodyMap::iterator it = mBehaviorBodyMap.begin(); it != mBehaviorBodyMap.end(); ++it)
	{
		delete (it->second);
	}

	mBehaviorBodyMap.clear();
}

IBehaviorBody* BehaviorBodyFactory::GetBehaviorBody(const CString& objectType) const
{
	CString objType = objectType;
	objType.MakeLower();

	BehaviorBodyMap::const_iterator it = mBehaviorBodyMap.find(objType);
	
	if(it != mBehaviorBodyMap.end())
		return it->second;

	return NULL;
}

void BehaviorBodyFactory::AddBehaviorBody(const CString& objectType, IBehaviorBody* pBody)
{
	CString objType = objectType;
	objType.MakeLower();

	BehaviorBodyMap::iterator it = mBehaviorBodyMap.find(objType);
	DATA_ASSERT(mBehaviorBodyMap.end() == it); // Check duplication.
	if(mBehaviorBodyMap.end() == it)
		mBehaviorBodyMap.insert(std::make_pair(objType, pBody));
}

void BehaviorBodyFactory::RemoveBehaviorBody(const CString& objectType)
{
	CString objType = objectType;
	objType.MakeLower();

	BehaviorBodyMap::iterator it = mBehaviorBodyMap.find(objType);
	if(it != mBehaviorBodyMap.end())
		mBehaviorBodyMap.erase(it);
}
