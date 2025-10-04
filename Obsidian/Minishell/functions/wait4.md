https://man7.org/linux/man-pages/man2/wait3.2.html

The `wait4` is similar to  [[waitpid]], but additionally return resource usage information about the child in the structure pointed to by rusage. 

- Purpose
	- Waits for a **==specific child process==**.
	- Can retrieve **exit status** and **resource usage**.

equivalent to:
```c
waitpid(pid, status,  options);
```

___
## Prototype

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

___
## Parameters

- **`pid`**: Which child to wait for (like [[waitpid]]):
    - `>0` → Specific child PID
    - `-1` → Any child    
    - `0` → Any child in the same process group    
    - `<-1` → Any child in a specific group    
- **`status`**: Exit info of child.
- **`options`**: 0 or **`WNOHANG`**
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

- PID of terminated child.
- **`0`** → if **`WNOHANG`** was used and no child has exited yet.
- **`-1`** → on error.