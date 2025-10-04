https://man7.org/linux/man-pages/man2/stat.2.html

The `lstat` function is similar to [[stat]], but it **does not follow symbolic links**. If the pathname refers to a symbolic link, `lstat` returns information about the link itself, not the file it points to. Otherwise, it behaves like [[stat]].

___
## Prototype

```c
#include <sys/stat.h>

int lstat(const char *pathname, struct stat *buf);
```

___
## Parameters

- **`pathname`**: Path to the file or symbolic link.
- **`buf`**: Pointer to a `struct stat` where the file or link information will be stored.
### struct stat

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat {
    dev_t     st_dev;     // ID of device containing file
    ino_t     st_ino;     // Inode number
    mode_t    st_mode;    // File type and mode (permissions)
    nlink_t   st_nlink;   // Number of hard links
    uid_t     st_uid;     // User ID of owner
    gid_t     st_gid;     // Group ID of owner
    dev_t     st_rdev;    // Device ID (if special file)
    off_t     st_size;    // Total size, in bytes
    blksize_t st_blksize; // Block size for filesystem I/O
    blkcnt_t  st_blocks;  // Number of 512B blocks allocated
    time_t    st_atime;   // Time of last access
    time_t    st_mtime;   // Time of last modification
    time_t    st_ctime;   // Time of last status change
};
```

- **`st_dev`** → Device identifier where the file resides.
- **`st_ino`** → Unique inode number.
- **`st_mode`** → File type and permissions (can use macros like `S_ISREG`, `S_ISDIR`).
- **`st_nlink`** → Number of hard links pointing to this file.
- **`st_uid` / `st_gid`** → Owner user and group IDs.
- **`st_rdev`** → Device ID for special files (like character or block devices).
- **`st_size`** → File size in bytes.
- **`st_blksize` / `st_blocks`** → File system block size and allocated blocks.
- **`st_atime`, `st_mtime`, `st_ctime`** → Access, modification, and status change timestamps.

___
## Example

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    struct stat st;

    if (lstat("symlink.txt", &st) == 0) {
        if (S_ISLNK(st.st_mode)) {
            printf("It is a symbolic link.\n");
        } else {
            printf("It is not a symbolic link.\n");
        }
    } else {
        perror("lstat");
    }

    return 0;
}
```

___
## Return

- **`0`** → Success, the `struct stat` is filled with information.
- **`-1`** → On error, and [[errno]] is set:
    - **`EACCES`** → Permission denied to access the file.
    - **`ENOENT`** → File does not exist.
    - **`ELOOP`** → Too many symbolic links encountered while traversing the path.
    - **`ENAMETOOLONG`** → Path name is too long.
    - **`EFAULT`** → `buf` points outside accessible memory.