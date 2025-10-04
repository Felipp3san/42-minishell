https://man7.org/linux/man-pages/man2/fork.2.html

`fork` creates a new process by duplicating the calling process. The new process is referred to as the _child_ process.  The calling process is referred to as the _parent_ process.

___
## Prototype

```c
#include <unistd.h>

pid_t fork(void);
```

___
## Example

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        printf("Hello from the child! PID = %d\n", getpid());
    } 
    else {
        // Parent process
        printf("Hello from the parent! Child PID = %d\n", pid);
    }

    return 0;
}
```

___
## Why is `fork()` important in shells?

When you type a command in a shell:

1. The shell calls `fork()` to create a child process.
2. In the **child**, it usually calls `execve()` (or another exec function) to replace its memory with the program you want to run.
3. The **parent** (the shell) calls `waitpid()` to wait for the child to finish before showing the next prompt.

___
## Return
 
On success, the [[PID]] of the child process is returned in the parent, and 0 is returned in the child.  On failure, -1 is returned in the parent, no child process is created, and [[errno]] is set to indicate the error.