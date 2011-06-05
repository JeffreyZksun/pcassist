#include "StdAfx.h"
#include "CloseLoopChecker.h"
#include <algorithm>

CloseLoopChecker::CloseLoopChecker(void)
: mOngoingItems()
{
}

bool CloseLoopChecker::PushOngoingItem(const CString& itemName)
{
	// Detect dead loop caused by the close loop reference.
	std::list<CString>::iterator it = std::find(mOngoingItems.begin(), mOngoingItems.end(), itemName);
	if(it != mOngoingItems.end())
	{
		// This variable is already in the stack. 
		// Close  loop reference is detected.
		// Return directly to avoid dead loop.
		//ASSERT(!_T("Close loop reference is detected"));

		return false;
	}
	else
		mOngoingItems.push_back(itemName);

	return true;
}

void CloseLoopChecker::Pop()
{
	if(!mOngoingItems.empty())
		mOngoingItems.pop_back();
}
