#pragma once

class ExecutionContext;

//////////////////////////////////////////////////////////////////////////
// IBehaviorBody
//////////////////////////////////////////////////////////////////////////

class IBehaviorBody 
{
public:
	virtual bool Execute(ExecutionContext*) = 0;
};



// Helper macros.

#define BEHAVIORBODY_DEC(BehaviorName) \
class BehaviorName : public IBehaviorBody\
{\
	virtual bool Execute(ExecutionContext*);\
};

#define BEHAVIORBODY_IMP(BehaviorName) \
	bool BehaviorName::Execute(ExecutionContext* pContext)


