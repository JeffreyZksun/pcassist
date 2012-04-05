#pragma once

class ParameterTable;
class BehaviorNode;
class BrainApplication;


class ExecutionContext
{
public:
	ExecutionContext(BrainApplication*, BehaviorNode*);

	const ParameterTable* const	GetInputParameterTable() const;

	void					SetBehaviorNode(BehaviorNode*);
	BehaviorNode* const		GetBehaviorNode() const;

	BrainApplication*		GetBrainApplication() const;

private:
	BrainApplication*		mpBrainApplication;
	BehaviorNode*			mpCurrentBehavior;
};

