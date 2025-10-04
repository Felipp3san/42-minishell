https://man7.org/linux/man-pages/man3/opendir.3.html

The `opendir` function opens a directory stream corresponding to the directory named by `name`. The returned directory stream can be used with [[readdir]], [[closedir]], and `rewinddir` to read the directory contents.

___
## Prototype

```c
#include <dirent.h>

DIR *opendir(const char *name);
```

___
## Parameters

- **`name`**: Path to the directory to be opened.

___
## Example

```c
#include <stdio.h>
#include <dirent.h>

int main(void) {
    DIR *dir = opendir("/tmp");
    struct dirent *entry;

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
```

___
## Return

- **Pointer to `DIR`** → Success, points to the directory stream.
- **`NULL`** → On error, and [[errno]] is set:
    - **`EACCES`** → Permission denied to open the directory.
    - **`ENOENT`** → Directory does not exist.
    - **`ENOTDIR`** → `name` is not a directory.
    - **`EMFILE`** → Process has too many files open.
    - **`ENOMEM`** → Insufficient memory to allocate the directory stream.