#pragma once

#include "IBehaviorBuilder.h"


class BehaviorBuilder : public IBehaviorBuilder
{
public:
	BehaviorBuilder();
	virtual ~BehaviorBuilder();

	virtual void InitializeBehaviorBodyFactory(BehaviorBodyFactory* pBehaviorBodyFactory);
};
