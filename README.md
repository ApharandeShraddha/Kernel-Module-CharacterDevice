# Kernel-Module-CharacterDevice
Implementation of a kernel module that creates a  character device.

---------------------------------------------------------------------------------------------------------------------------------------
Project Description:

Implementation of a kernel module that creates a /dev/process_list character device. The character device supports the read() operation. When the read() system call is invoked on character device from a user space process, kernel module  returns following information for all currently running processes:

process ID
parent process ID
the CPU on which the process is running
its current state.

----------------------------------------------------------------------------------------------------------------------------------------
Sample output:

	PID=1 PPID=0 CPU=4 STATE=TASK_RUNNING
	PID=2 PPID=0 CPU=2 STATE=TASK_INTERRUPTIBLE
	PID=10 PPID=2 CPU=0 STATE=TASK_UNINTERRUPTIBLE
	PID=16434 PPID=16424 CPU=10 STATE=TASK_DEAD
	PID=14820 PPID=16424 CPU=8 STATE=TASK_WAKEKILL,TASK_UNINTERRUPTIBLE
	...and so forth
	
---------------------------------------------------------------------------------------------------------------------------------------

FILES:

  kernelProcessList -> Kernel Module.
  userProcessList  -> user module.
  process_list.h   -> header file with delcaration of buffer used by kernel and user module.
  parse_file.h     -> Used by user module having parsing logic to covert long value of state					to actual state name.   

---------------------------------------------------------------------------------------------------------------------------------------

TO RUN:
 Execute following commands in ORDER mentioned below: 

 1. make
 2. make insert
 3. make access
 4. make usercode
 5. make run


To Remove kernel module:
 make remove

