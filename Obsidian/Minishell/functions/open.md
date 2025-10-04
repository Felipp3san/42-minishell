https://man7.org/linux/man-pages/man2/openat.2.html

The `open` function opens a file (or creates it if it doesn’t exist, when **`O_CREAT`** is specified in _flags_).

___
## Prototype

```c
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

____
## Parameters

- **`pathname`**: Path to the file you want to open.  
	Example: `"file.txt"`, `"/home/user/data.log"`
- **`flags`**: Controls how the file is opened.  
	Common flags:
	- `O_RDONLY` → Open for **read only**
	- `O_WRONLY` → Open for **write only**
	- `O_RDWR` → Open for **read and write**
	- `O_CREAT` → Create file if it doesn’t exist (requires `mode`)
	- `O_TRUNC` → Truncate file to zero length if it exists
	- `O_APPEND` → Write operations go to the end of the file
	- `O_EXCL` → Used with `O_CREAT`, ensures the call fails if the file already exists
	You can **combine** flags with `|` (bitwise OR).
- **`mode`**: Defines permissions for the new file (similar to Unix `chmod`).  
    Only needed when creating a file (`O_CREAT`).  
	Example:
	- `0644` → User read/write, group read, others read
	- `0600` → User read/write only

___
## Example

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open file for writing, create if it doesn’t exist, truncate if it does
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, world!\n", 14);  // write using the file descriptor

    close(fd);  // always close after use
    return 0;
}
```

____
## Return

- **Success:** A **non-negative integer** file descriptor.
- **Failure:**  returns `-1` and sets [[errno]].
	- **`ENOENT`** → The file does not exist and `O_CREAT` was not specified.
	- **`EACCES`** → Permission denied (file or directory access rights).
	- **`EEXIST`** → File exists but `O_CREAT | O_EXCL` was specified.
	- **`EISDIR`** → Tried to open a directory for writing.
	- **`EMFILE`** → The process already has the maximum number of file descriptors open.