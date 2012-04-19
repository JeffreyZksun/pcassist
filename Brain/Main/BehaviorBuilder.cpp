
#include "BehaviorBuilder.h"
#include "Actions.h"
#include "Conditions.h"
#include "BehaviorBodyFactory.h"

BehaviorBuilder::BehaviorBuilder()
{

}

BehaviorBuilder::~BehaviorBuilder()
{

}

#define ADD_BEHAVIORBODY_TO_FACTORY(BehaviorName) \
	pBehaviorBodyFactory->AddBehaviorBody(_T(#BehaviorName), new BehaviorName());

void BehaviorBuilder::InitializeBehaviorBodyFactory(BehaviorBodyFactory* pBehaviorBodyFactory)
{
	DATA_ASSERT(pBehaviorBodyFactory != NULL);
	if(NULL == pBehaviorBodyFactory)
		return;

	// Conditions
	ADD_BEHAVIORBODY_TO_FACTORY(CompositeCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(FileExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(FolderExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(RegisterKeyExistsCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(ProcessRunningCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(ActionResultCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(TrueCondition);
	ADD_BEHAVIORBODY_TO_FACTORY(FalseCondition);


	// Actions
	ADD_BEHAVIORBODY_TO_FACTORY(ComplexAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CreateFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(DeleteFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CopyFileAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CreateFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(DeleteFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(CopyFolderAction);
	ADD_BEHAVIORBODY_TO_FACTORY(MakeDirectoryLinkAction);
	ADD_BEHAVIORBODY_TO_FACTORY(RunSystemCommandAction);
	ADD_BEHAVIORBODY_TO_FACTORY(RunProcessAction);
	ADD_BEHAVIORBODY_TO_FACTORY(ConditionBlockAction);
	ADD_BEHAVIORBODY_TO_FACTORY(TaskListAction);
	ADD_BEHAVIORBODY_TO_FACTORY(ConditionListCheckAction);
	ADD_BEHAVIORBODY_TO_FACTORY(ChangeVariableAction);
	ADD_BEHAVIORBODY_TO_FACTORY(EmptyAction);

}
