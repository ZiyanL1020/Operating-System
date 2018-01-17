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
- Implement each producer/consumer task as a process. Use message queue as the
bounded buffer for inter-task communications. Note that shared memory access is taken care of by the operating system
message passing facility. However, kernel memory is finite, and thus there cannot be
an unbounded number of messages outstanding; at some point the producer must
stop generating messages and the consumer must consume them, otherwise the kernel’s
memory will be completely consumed with messages, blocking the sender from
further progress. What is needed, therefore, is to set up the correct queue size. When
the queue is full, the producer is blocked by the system and cannot continue to send
messages until a message is consumed.
- Create a process with a fixed buffer size in which producers and consumers are threads
within the process and the buffer is a shared global data structure such as a circular
queue that all threads share access to. Note that shared memory access needs to be
taken care of at the application level. The POSIX thread semaphore and mutex are
to be used for concurrency control.

## Memory management in Linux
- Implement two memory allocation algorithms: best fit and worst fit. For
each allocation algorithm, you will first implement a memory initialization function, which
requests a chunk of free memory dynamically from the system to be managed by different
allocation algorithms. Then you will implement an allocation function and a de-allocation
function. One utility function will also be implemented to help analyze the efficiency of
allocation algorithm and its implementation. Then, you will write a number of tests to
test the correctness of your implementations. Finally, you will write an analysis on the
strengths and weaknesses of the two different allocation algorithms.

