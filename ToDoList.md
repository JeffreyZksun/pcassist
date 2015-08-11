List the tasks to be done.

# P1 (Will be done soon) #


  * Refactor the dead loop check for the parameter evaluation.Use the same algorithm as behavior execution.
  * Refactor: Make the behavior factor as a singleton. There doesn't need a factory for each application instance.
  * Refactor: Rename ComplexAction as ConditionalAction.



# P2 #

  * Rename ComplexCondition as CompositeCondition. Change the implementation to support the expression. Such as C1 && C2 || ( C3 && C4).


# P3 (Will be done but long lead) #
  1. Rename ObjectID to Name.
  1. Rename ObjectType to Type.
  1. Change Comments to xData in the Parameter
  1. Update the xml doc version. save the paramter name, value, xdata as attributes.
  1. Support load migrate and downgrade save.
  1. Make the task automation logical platform independent.

# P4 (wish list) #
  1. Support multiple file format.
  1. Support thread safe.


# Task items done #

  * Add a new action named ConditionBlockAction. It will loop to check the specified condition with the specified interval. It is blocked until the condition is true or time is out. If condition is met, return true. Otherwise, it means timeout, return false.
  * Avoid dead loop for behavior execution. Add a member variable bool mbIsWorking to Behavior class. Before executing check if its value is true, if yes, a dead loop is detected. Log error and return. If no, set it to be true, do the execution. After the execution, set its value to false. Delete the dead loop check for condition and action.
  * Don't write the built in global variables to the xml. Use mUserParamterTable to save the user defined parameters and mBuiltinParamterTable to save the built-in parameters.
  * Add a new condition named ActionResultCondition. It executes an action. And check if the result is equal to the expected result. If equal, the condition is true.
  * Add new action ConditionListCheckAction
Check all the conditions in the list. Return true if all the conditions are true. Otherwise return false.

This action can be used as sanity check.

The syntax for condition list parameter is like
```
<Parameter>
	<Name>ConditionList</Name>
	<value>
		{1.1 Is there running process setup.exe}
		{1.2 Is there running process misc}
		{1.3 Does zip work}
		{1.4 Does the compiler work.}
	</value>
</Parameter>
```

  * Refactor: In task manager, save the list of action ids as the task list. Currently, it saves the list of pointer points to the registered action. Register and unregister action don't affect the task list. Task list can save a action id which is NOT registered. When add a action id to task list, don't check if the action exists. Just add it. When execute the task list, log out warnings for the missed action.

  * Add a new action named TaskListAction. It references a action id list. During execution it executes the referenced action one by one. The result of the last action is result.