#pragma once

class ParameterTable;
class BehaviorNode;
class TaskSystem;


class ExecutionContext
{
public:
	ExecutionContext(TaskSystem*, BehaviorNode*);

	const ParameterTable* const	GetInputParameterTable() const;

	void					SetBehaviorNode(BehaviorNode*);
	BehaviorNode* const		GetBehaviorNode() const;

	TaskSystem*		GetTaskSystem() const;

private:
	TaskSystem*		mpTaskSystem;
	BehaviorNode*			mpCurrentBehavior;
};

