https://man7.org/linux/man-pages/man2/dup.2.html

`dup2` duplicates an existing file descriptor to a **specified target descriptor**.  Unlike [[dup]], which chooses the lowest available descriptor, `dup2` lets you **explicitly set the new descriptor number**.  

It is commonly used to **redirect standard input/output** in shell-like programs.

___
## Prototype

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```

___
## Parameters

- **`oldfd`**: The file descriptor to be duplicated.
    - Must be a valid, open file descriptor.        
- **`newfd`**: The desired new file descriptor.
    - If `newfd` is already open, it is **closed first** before duplicating `oldfd`.
    - If `oldfd` equals `newfd`, `dup2` does nothing and returns `newfd`.

___
## Example

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    // Open a file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Duplicate fd into stdout (1)
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    // Now printf goes to output.txt instead of terminal
    printf("This text goes into the file!\n");

    close(fd);
    return 0;
}
```

___
## Return

- On **success**: returns `newfd`.
- On **failure**: returns `-1` and sets [[errno]].
	- **`EBADF`** → `oldfd` is not a valid open file descriptor.
	- **`EBADF`** → `newfd` is out of the allowed range for file descriptors.
	- **`EMFILE`** → The process has reached its maximum number of file descriptors.
	- **`EINTR`** → Interrupted by a [[terms/signal]] before duplication.