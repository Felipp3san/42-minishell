https://man7.org/linux/man-pages/man2/kill.2.html

`kill` sends a signal **`sig`** to one or more processes identified by **`pid`**. It does not only kill processes — it can deliver any signal (e.g., **`SIGTERM`**, **`SIGUSR1`**, **`SIGCONT`**, etc.).

___
## Prototype

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

___
## Parameters

- **`pid`**: Target process ID(s):
    - `>0` → Specific process with that PID
    - `0` → All processes in the caller’s process group
    - `<-1` → All processes in process group `-pid`
    - `-1` → All processes the caller has permission to signal
- **`sig`**: The signal number to send:
    - `0` → No signal is sent (only error/permission checking). Useful to test whether a process exists and whether you have permission to signal it.
    - Any valid signal (e.g. `SIGTERM`, `SIGKILL`, `SIGHUP`, etc.)

___
## Example

```c
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    pid_t pid = 12345; // example PID
    if (kill(pid, SIGTERM) == -1) {
        if (errno == ESRCH) {
            fprintf(stderr, "Process %d does not exist\n", pid);
        } else if (errno == EPERM) {
            fprintf(stderr, "No permission to signal process %d\n", pid);
        } else {
            fprintf(stderr, "kill error: %s\n", strerror(errno));
        }
        return 1;
    }
    printf("SIGTERM sent to %d\n", pid);
    return 0;
}
```

___
## Return

- **`0`** on success.
- `-1` on error and sets [[errno]]. Common `errno` values:
	- `ESRCH` — no such process (target doesn't exist).
	- `EPERM` — you don’t have permission to send the signal to the target.
	- `EINVAL` — invalid signal number.