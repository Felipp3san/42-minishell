https://man7.org/linux/man-pages/man3/wait.3p.html

The `wait` function is used by a **parent process** to wait for one of its **child processes** to finish execution. It allows the parent to:

1. Reap the child process (clean up its resources).
2. Get the **exit status** of the child.

Without calling `wait` (or [[waitpid]]), child processes that terminate become **zombie processes**—they are dead but still occupy an entry in the process table.
   
==The _wait_() function shall cause the calling thread to become blocked.==

___
# Prototype

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
```

___
## Parameters

- **`status`**: Pointer to an integer where the child’s exit info is stored.
	- If you pass `NULL`, the exit status is ignored.

____
## Example

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child running\n");
        sleep(2);
        return 42;
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status);  // Wait for child to finish

        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        }
    } else {
        perror("fork failed");
    }

    return 0;
}
```

___
## Key points

- wait blocks the parent until any child terminates.
- If multiple children exist, wait only handles one at a time.
- To wait for a specific child, use waitpid instead.
- Helps prevent zombie processes.
  
  You can use macros like:
	- `WIFEXITED(status)` – true if the child exited normally.
		- Always check for true before retrieving the exit status.
	- `WEXITSTATUS(status)` – retrieves the exit code.
	- `WIFSIGNALED(status)` – true if the child was terminated by a signal.

___
## Return

- Returns the **PID of the terminated child** on success.
- Returns `-1` on error (e.g., no child processes exist).