https://man7.org/linux/man-pages/man2/dup.2.html

`dup` duplicates an existing file descriptor.  The new file descriptor refers to the **same open file description** (same underlying file, offset, and access mode) as the original, but uses the **lowest available descriptor number**.  

This is often used to redirect standard input/output (e.g., replace `stdout` with a file).

___
## Prototype

```c
#include <unistd.h>

int dup(int oldfd);
```

___
## Parameters

- **`oldfd`**: The file descriptor to be duplicated.
    - Must be a valid open file descriptor.

___
## Example

**Duplicating a file fd and writing to it via the new fd**
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

    // Duplicate the file descriptor
    int newfd = dup(fd);
    if (newfd == -1) {
        perror("dup");
        return 1;
    }

    // Write using the new descriptor
    const char *msg = "Hello via duplicated fd!\n";
    write(newfd, msg, 25);

    close(fd);
    close(newfd);
    return 0;
}
```

**Duplicating `stdout` and writing to it via new fd**
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    // Duplicate the file descriptor
    int newfd = dup(STDOUT_FILENO);
    if (newfd == -1) {
        perror("dup");
        return 1;
    }

    // Write to stdout using the new descriptor
    const char *msg = "Hello via duplicated fd!\n";
    write(newfd, msg, 25);

    close(newfd);
    return 0;
}
```

___
## Return

- On **success**: returns the **new file descriptor** (lowest unused number).
- On **failure**: returns `-1` and sets [[errno]].
	- **`EBADF`** → `oldfd` is not a valid open file descriptor.
	- **`EMFILE`** → The process already has the maximum number of file descriptors open.

