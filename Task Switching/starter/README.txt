Memory pool has 20 blocks.
We have five tasks in the test.

Task1 is the original infinite loop, has priority 1.
Task2 print out the stats of all task periodically, has priority 5.
Task3 allocates 15 blocks, wait for 10 sec, then free 15 blocks, has priority 4.
Task4 allocates 15 blocks, has priority 3.
Task5 allocates 5 blocks, has priority 2.

Initially, all tasks are created.

Task3 has the highest priority, it allocates 15 blocks, and delay for 10 sec. Then Task4 tries to allocates 15 blocks,
but only 5 available, so it allocates 5 blocks and get blocked. Task5 tried to allocates but memory is not available,
it fails and get blocked.

After Task3 free 15 blocks, Task4 has higher priority, it gets remaining 10 blocks. Right now there are only 5 blocks
left, and Task5 gets the rest. 