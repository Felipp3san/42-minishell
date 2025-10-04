https://man7.org/linux/man-pages/man3/waitpid.3p.html

`waitpid` is a more **flexible version of [[wait]]. It lets the parent process:

1. Wait for a **specific child** or group of children.
2. Optionally **not block** if the child hasn’t exited yet.
3. Retrieve the child’s **exit status**, just like [[wait]].

___
## Prototype

```c
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```

___
## Parameters

- **`pid`**: Which child process to wait for:
    - `> 0` → Wait for the child with this specific PID.
    - `-1` →Wait for **any child** (behaves like [[wait]]).
    - `0` → Wait for any child in the **same process group** as the parent.
    - `< -1` → Wait for any child whose **process group ID = |pid|**.
- **`status`**: Pointer to an integer to store the child’s exit status (same as [[wait]]).
- **`options`**: Flags that modify behavior:
    - `0` → Default; **blocks** until child exits.
    - `WNOHANG` → **Do not block**; return immediately if child hasn’t exited.
    - `WUNTRACED` → Also return if a child has **stopped** (e.g., via `SIGSTOP`).
    - `WCONTINUED` → Return if a stopped child **resumes**.

___
## Example

**Blocking**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child running...\n");
        sleep(3);
        printf("Child exiting.\n");
        exit(7);
    } else {
        // Parent process
        int status;
        printf("Parent waiting for child...\n");
        pid_t child_pid = waitpid(pid, &status, 0); // Wait specifically for this child

        if (WIFEXITED(status)) {
            printf("Child %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
```

**Non-blocking**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	pid_t pid = fork();
	
	if (pid == 0) {
	    sleep(5);
	    _exit(0);
	} else {
	    int status;
	    pid_t result;
	    do {
	        result = waitpid(pid, &status, WNOHANG); // Non-blocking
	        if (result == 0) {
	            printf("Child still running...\n");
	            sleep(1);
	        }
	    } while (result == 0);
	
	    printf("Child finished\n");
	}
	
    return 0;
}
```

___
## Return

- Returns the PID of the child whose state changed.
- **`0`** → if **`WNOHANG`** was used and no child has exited yet.
- **`-1`** → on error (e.g., no such child exists).