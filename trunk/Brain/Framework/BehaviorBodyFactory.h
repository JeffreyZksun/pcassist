#pragma once
#include <map>

class IBehaviorBody;


class BehaviorBodyFactory
{
public:
	BehaviorBodyFactory(void);
	~BehaviorBodyFactory(void);

	IBehaviorBody*		GetBehaviorBody(const CString& objectType) const;
	void				AddBehaviorBody(const CString& objectType, IBehaviorBody* pBody);
	void				RemoveBehaviorBody(const CString& objectType);

private:
	typedef std::map<CString, IBehaviorBody*> BehaviorBodyMap;

	BehaviorBodyMap		mBehaviorBodyMap;
};
