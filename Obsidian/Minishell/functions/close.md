https://man7.org/linux/man-pages/man2/close.2.html

The `close` function closes an open file descriptor, so it no longer refers to any file and may be reused.
- The kernel releases the underlying file, socket, or device resource.
- If a file was opened multiple times (different descriptors), each descriptor must be closed separately.

___
## Prototype

```c
#include <unistd.h>

int close(int fd);
```

___
## Parameters

- **`fd`**: File descriptor returned by [[open]], [[dup]], `socket`, etc.

___
## Example

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    printf("File closed successfully.\n");
    return 0;
}
```

___
## Return

- **Success:** returns `0`.
- **Failure:** returns `-1` and sets [[errno]].
	- **`EBADF`** → `fd` is not a valid open file descriptor.
	- **`EINTR`** → The call was interrupted by a signal before it could complete.
	- **`EIO`** → An I/O error occurred while flushing or updating file information.