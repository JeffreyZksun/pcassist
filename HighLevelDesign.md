# Design #

The exction context is the bridge between behavior node and behavior body. The behavior node populate the context. All the required information by the body can be got from the context.

The paramter related classes constitute a independent pamerater sub-system. Such as parameter, parameter table and variable manager. It doesn't depends on the BrainAPplication or Behavior factory.


# Modules #
## Coordinator.exe ##
A monitor process is always on live. It monitors the conditions and exectes the related action when the condition is meet.

  * It is lightweight and with high performance.
  * It consumes very little system resources.

## Executor.exe ##
  * It accepts a transcript, analyze and execute it immediately.
  * It won't be blocked during execution.
  * It logs all the execution results and then exit.

## Reporter.exe ##
  * It analyzes the log results.

## Communicator.exe ##
  * Communicate cross network.




## Brain.dll ##
  * It defines the data models of the system. All other assemblies only define the logic.
  * Support the data types the less the better.


# Design Principles #
  * Use multi-processes prior to the multi-threads.
    * Benefits: Don't need to and the lock code everywhere, which is hard to maintain.
  * Use the tcp or upper layer protocols to implement the cross process communicataion.
    * Benefits: Both the local process and remote process can adopt this communication.