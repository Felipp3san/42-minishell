https://man7.org/linux/man-pages/man2/chdir.2.html

The **`chdir`** function changes the **current working directory** of the calling process to the directory specified by `path`.
- All relative paths in subsequent file operations are interpreted relative to the new current directory.
- Only affects the calling process (not other processes).

___
## Prototype

```c
#include <unistd.h>

int chdir(const char *path);
```

___
## Parameters

- **`path`**: Path to the directory you want to switch to.  
    Example: `"."` for current directory, `".."` for parent, `"/home/user"` for absolute path.

____
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    if (chdir("/home/user") == -1) {
        perror("chdir");
        return 1;
    }

    printf("Current directory changed successfully.\n");
    return 0;
}
```

____
## Return

- **Success:** returns `0`.
- **Failure:** returns `-1` and sets [[errno]].
	-  **`ENOENT`** → The specified path does not exist.
	- **`ENOTDIR`** → A component of the path is not a directory.
	- **`EACCES`** → Permission denied to access the directory.
	- **`EMFILE` / `ENFILE`** → Rare, system limits reached (process or system file table).