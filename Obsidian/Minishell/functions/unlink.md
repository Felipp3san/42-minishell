https://man7.org/linux/man-pages/man2/unlink.2.html

The `unlink` function removes (deletes) a name from the filesystem. If that name was the last link to a file and no process has the file open, the file’s resources are freed. If other links or open file descriptors exist, the file is only removed from the directory, and the data remains until all descriptors are closed.

___
## Prototype

```c
#include <unistd.h>

int unlink(const char *pathname);
```

___
## Parameters

- **`pathname`**: Path to the file to be removed.

___
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    if (unlink("example.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("unlink");
    }
    return 0;
}
```

___
## Return

- **`0`** → Success, the file link was removed.
- **`-1`** → On error, and [[errno]] is set:
    - **`EACCES`** → Write permission denied for the directory containing the file.
    - **`EPERM`** → Attempt to remove a read-only file or a file with immutable attributes.
    - **`EISDIR`** → `pathname` refers to a directory (use `rmdir` for directories).
    - **`ENOENT`** → File does not exist.
    - **`ENOTDIR`** → A component of the path is not a directory.
    - **`EFAULT`** → `pathname` points outside accessible memory.