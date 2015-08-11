  * The execution of the tasks is implemented by the command pattern.
    * When receive a text message from network, translate it into a task object and add it to the task manager.
    * The task manager traverse all the tasks and execute them.

  * The task structure is implemented by the decorator pattern.
    * Basically there are two kinds of tasks. One is immediate task and the other is the conditional task.
    * The immediate task executes the action list directly.
    * The conditional task only be executed when some condition is met. For example, the time is later than the desired value, or some dependency is ready.
    * The conditional task decorates the basic task with the condition.

  * The event notification is implemented by the observer pattern.
    * The event sink subscribes the event.
    * The event source fire the event.
    * The notification manger check the subscriptions and dispatches the event to the corresponding event sink.
    * The dispatcher and event filer are the optimization to this design.

  * Network communication.
    * It is implemented by the asynchronous fashion.
    * All the network connections are handled in a thread.