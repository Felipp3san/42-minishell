https://man7.org/linux/man-pages/man2/wait3.2.html

The `wait3` is similar to [[waitpid]], but additionally return resource usage information about the child in the structure pointed to by rusage. 

- Purpose
	- Waits for **==any child process==** to terminate.
	- Provides **resource usage information** (CPU time, memory usage) for the child.

equivalent to:
```c
waitpid(-1, status,  options);
```

___
## Prototype

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

pid_t wait3(int *status, int options, struct rusage *rusage);
```

___
## Parameters

- **`status`**: Like wait, stores exit status of the child.
- **`options`**: Same as [[waitpid]]:
	- **`0`** → Block until a child exits
	- **`WNOHANG`** → Return immediately if no child has exited
- **`rusage`**: Pointer to struct rusage to store resource usage of the terminated child (CPU time, memory, I/O, etc.). Can be NULL if you don’t need it.

___
## Some fields in rusage struct

- `ru_utime` → User CPU time used
- `ru_stime` → System CPU time used
- `ru_maxrss` → Maximum resident set size (memory)
- `ru_inblock` → Block input operations
- `ru_oublock` → Block output operations

___
## Return

- PID of terminated child, or -1 on error.
-  like [[wait]], but also fills rusage struct.