#pragma once

#include <list>

class CloseLoopChecker
{
public:
	CloseLoopChecker(void);

	// Return false if the new item already exist. It indicates a close loop is detected.
	bool		PushOngoingItem(const CString&);
	void		Pop();

private:
	std::list<CString> mOngoingItems;
};
