https://man7.org/linux/man-pages/man2/access.2.html

The `access` function in C is used to check a file’s accessibility according to the real user ID (UID) and group ID (GID) of the calling process. It does **not** open the file—it just checks whether the requested permission would be granted if you attempted to use it.

___
## Prototype

```c
#include <unistd.h>

int access(const char *path, int mode);
```

___
## Parameters

- **`path`**: Path to the file you want to check.
- **`mode`**: What type of accessibility check you want. It can be one or more of these flags:
    - `F_OK` → Check if the file exists.
    - `R_OK` → Check for read permission.
    - `W_OK` → Check for write permission.
    - `X_OK` → Check for execute/search permission (execute if file, search if directory).

You can combine flags using the bitwise OR operator (`|`).

___
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *file = "test.txt";

    if (access(file, F_OK) == 0) {
        printf("File exists.\n");

        if (access(file, R_OK) == 0) {
            printf("Readable.\n");
        }
        if (access(file, W_OK) == 0) {
            printf("Writable.\n");
        }
        if (access(file, X_OK) == 0) {
            printf("Executable.\n");
        }
    } else {
        perror("File check failed");
    }

    return 0;
}
```

___
### Return

- **`0`** → Success (the file exists and has the requested permissions).
- **`-1`** → Error (and sets [[errno]]):
    - `EACCES`: Permission denied.
    - `ENOENT`: File does not exist.
    - `ENOTDIR`: Part of the path is not a directory.
    - `EROFS`: Attempting to check for write on a read-only filesystem.
    - And others depending on the situation.