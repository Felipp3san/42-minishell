https://man7.org/linux/man-pages/man3/readdir.3.html

The `readdir` function reads the next entry from the directory stream pointed to by `DIR *dirp`. Each call returns information about a single directory entry in a `struct dirent`. When the end of the directory is reached, it returns `NULL`.

___
## Prototype

```c
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

___
## Parameters

- **`dirp`**: Pointer to an open directory stream (from [[opendir]]).

### struct dirent 

```c
#include <dirent.h>

struct dirent {
    ino_t          d_ino;       // Inode number
    off_t          d_off;       // Offset to the next dirent
    unsigned short d_reclen;    // Length of this record
    unsigned char  d_type;      // Type of file (DT_*)
    char           d_name[256]; // Null-terminated filename
};
```

- **`d_ino`** → Inode number of the file.
- **`d_off`** → Offset to the next directory entry (used internally by the system).
- **`d_reclen`** → Length of this `dirent` record.
- **`d_type`** → Type of file; can be one of the macros:
    - `DT_REG` → Regular file
    - `DT_DIR` → Directory
    - `DT_LNK` → Symbolic link
    - `DT_CHR` → Character device        
    - `DT_BLK` → Block device
    - `DT_FIFO` → FIFO/pipe
    - `DT_SOCK` → Socket
    - `DT_UNKNOWN` → Unknown type
- **`d_name`** → Null-terminated name of the file or directory (up to 255 characters)

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
        printf("Name: %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
```

___
## Return

- **Pointer to `struct dirent`** → Success, points to the next directory entry. 
	- This structure may be statically allocated; do not attempt to [[free]] it.
- **`NULL`** → End of directory or on error, and [[errno]] is set if an error occurred:
    - **`EBADF`** → `dirp` is not a valid directory stream.
    - **`EFAULT`** → `dirp` points outside accessible memory.
    - **`EINVAL`** → Directory stream is invalid.