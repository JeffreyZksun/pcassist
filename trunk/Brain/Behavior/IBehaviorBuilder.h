#pragma once

// The IOSProvider encapsulates all the work to add behavior body to the behavior factory.

class BehaviorBodyFactory;

class IBehaviorBuilder
{
public:
	virtual ~IBehaviorBuilder() {}

	virtual void InitializeBehaviorBodyFactory(BehaviorBodyFactory* pBehaviorBodyFactory) = 0;

};
