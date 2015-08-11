# Design Overview #
The project is to develop a task automation system. In the system, the work we need to do is broken into a task list. The tasks can be either dependent or independent with each other. The system accepts the task list and execute them automatically. If some sub task sets are independent with others, they can be distributed to different computation nodes to implement the concurrency.


If the task can be executed by following the predefined rules and doesn't need the decision made by human being during the execution process, this task can be automated. This kind of tasks can be summarized by a single sentence "**When the condition is met, execute the action**".

The condition might be
  * The scheduled time is up
  * The notification is received
  * ...

The action might be
  * Start process.
  * Create/delete/copy folder/file.
  * Build the project.
  * ...


# Task Automation System #
## Computation Node ##
The Computation Node is the something which actually executes the computation. It can be a physical machine, virtual machine, smart phone, embedded device and anything else as long as it can execute the computation specified by the task. The computation nodes constitute the physical network.

## Coordinator ##
There is a coordinator instance running on each computation node. The coordinators communicate with each other to constitute the commutation network. All the communication between computation nodes in the system is by way of the coordinator. The communication is based on the Task Automation Transfer Protocol (TATP).

The coordinator is the role to accept the task list. When the coordinator (say master) accepts a task list, it will breaks the list into some sub lists and dispatch them to different coordinators (say slaves), including itself. Then the slave coordinators execute the dispatched task list concurrently. Actually the slave coordinators just delegate the tasks to the executors.

The coordinator has the responsibilities below
  1. Call the executor to execute the tasks.
  1. Get the execution status of the executor in real time.
  1. Communicate with other coordinators.

## Executor ##
It is the role who actually execute the tasks. It accepts a task list, then execute it and generate the report.