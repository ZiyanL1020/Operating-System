# Operating-System
Operating system programming projects built with ARM RL-RTX that supports ARM Cortex-M3 processors on Keil MCB1700 boards

## Introduction to ARM RL-RTX application and kernel programming
- Add a primitive to RL-RTX API to return the number of active tasks in the system.
     - int os_tsk_count_get (void);
     - A task is considered active when its state is not set to INACTIVE in the TCB. The os idle task is a valid task that you should check the state as well.
- Implement a new primitive to obtain the task status information from the RTX at runtime given the task id. The function description is as follows.
  - OS_RESULT os_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer)
- Create five testing tasks to demonstrate that you have successfully implemented the required primitives Your test tasks should do the following tests.
  - One of the tasks calls the os_tsk_count_get primitive to test the number of active tasks in the system returned by the function.
  - One of the tasks periodically prints task status of each task in the system by calling the os_tsk_get primitive.

## Task switching in ARM RL-RTX
- The primitives to be added are described as follows.
  - void *os_mem_alloc (void *box_mem)
  - OS_RESULT os_mem_free (void *box_mem, void *box)
- Create a set of testing tasks to demonstrate that you have successfully implemented the required primitives. 
  - A task can allocate a fixed size of memory.
  - A task will get blocked if there is no memory available when os_mem_alloc() is called.
  - A blocked on memory task will be resumed once enough memory is available in the system.
  - Create a testing scenario that multiple tasks with different priorities are all blocked waiting for memory. When memory becomes available, test whether it is the highest priority task that waits the longest that gets the memory first.
## Inter-task communication and concurrency in Linux

## Memory management in Linux
