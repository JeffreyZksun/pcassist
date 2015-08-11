This page defines the responsibility of the classes.

# IDatabaseObject #
## Description ##
It is an interface. All the classes which need persist data are derived from this class.

# Parameter #
## Class Hierarchy ##
```
IDatabaseObject
	Parameter
```

# ParameterTable #
## Class Hierarchy ##
```
IDatabaseObject
	ParameterTable
```

# Behavior, Action, Condition #

## Class Hierarchy ##
```
IDatabaseObject
	Behavior
		Action
		Condition
```
## Description ##
The Behavior class represents behavior to be executed. Its general workflow is doing something based on the input and generate the output.

In logic, the condition and action are the same. They represent behaviors. The minor difference is condition generally makes some CHECKS and action generally makes some CHANGES.

The Behavior class only maintains the ParameterTable for the input and output. All the execution logic is delegated to the behavior body.

The parameter table contains an ObjectId and behavior body name. The ObjectId is a unique id which is used to retrieve this behavior. The behavior body name is a name which is used to get the related behavior body from the behavior body factory.

# ExecutionContext #
## Description ##
It works as the medium to pass though the data from action to action. It resolves the problem when pass the result of an action to its following one.

Member functions
```
	AddInputParameter()
	AddOuputParameter()
	ClearInputParameters()
	MoveOutputParametersToInputParameters()
	GetInputParameter()
```


# IBehaviorBody #
## Description ##
This is the interface for the executor. It declares the general behaviors which all the concrete behavior bodies should have. Its basic behavior is doing something based on the input and generate output.

```
	bool Execute(ExecutionContext*)
	{
		// Get input
		
		// Do the action
		
		// Generate output 

		// Return result
	}
```

## Methods ##
| **Name** | **Description** |
|:---------|:----------------|
| Execute  | Execute the action this behavior body should do |

# BehaviorBodyFactory #
BehaviorBodyFactory maintains a map of the name and the concrete behavior body.