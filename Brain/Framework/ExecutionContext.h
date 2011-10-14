#pragma once

class ParameterTable;
class BehaviorNode;

class ExecutionContext
{
public:
	ExecutionContext(BehaviorNode*, ParameterTable*);

	void					SetInputParameterTable(ParameterTable*);
	ParameterTable* const	GetInputParameterTable() const;

	void					SetBehaviorNode(BehaviorNode*);
	BehaviorNode* const		GetBehaviorNode() const;

private:
	ParameterTable*			mpInputTable;
	BehaviorNode*			mpCurrentBehavior;
};

