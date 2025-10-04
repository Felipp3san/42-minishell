https://man7.org/linux/man-pages/man3/closedir.3.html

The `closedir` function closes a directory stream opened by [[opendir]]. It releases any resources associated with the directory stream. After calling `closedir`, the `DIR *` pointer becomes invalid and must not be used.

___
## Prototype

```c
#include <dirent.h>

int closedir(DIR *dirp);
```

___
## Parameters

- **`dirp`** → Pointer to an open directory stream to be closed.

___
## Example

```c
#include <stdio.h>
#include <dirent.h>

int main(void) {
    DIR *dir = opendir("/tmp");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read entries here with readdir...

    if (closedir(dir) == 0) {
        printf("Directory closed successfully.\n");
    } else {
        perror("closedir");
    }

    return 0;
}
```

___
## Return

- **`0`** → Success, the directory stream was closed.
- **`-1`** → On error, and [[errno]] is set:
    - **`EBADF`** → `dirp` is not a valid open directory stream.
    - **`EFAULT`** → `dirp` points outside accessible memory.