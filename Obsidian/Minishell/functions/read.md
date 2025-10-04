https://man7.org/linux/man-pages/man2/read.2.html

`read` attempts to read data from a file descriptor into a buffer.  It is a **low-level system call** used for input from files, pipes, sockets, terminals, etc.  

Unlike higher-level functions (`fread`, `scanf`), `read` works directly with file descriptors, not file streams.

___
## Prototype

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

___
## Parameters

- **`fd`**: File descriptor from which to read.
    - Typically obtained from [[open]], `socket`, [[pipe]], or [[dup]].
    - Standard file descriptors: 
		- `0` → **`stdin`**, 
		- `1` → **`stdout`**, 
		- `2` → **`stderr`**.
- **`buf`**: Pointer to a memory buffer where the read data will be stored.
- **`count`**: Maximum number of bytes to read into `buf`.

___
## Example

```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    char buffer[128];
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes] = '\0'; // Null-terminate to use as string
    printf("Read %zd bytes: %s\n", bytes, buffer);

    close(fd);
    return 0;
}
```

___
## Return

- On success: returns the number of bytes actually read.
	- This may be less than **`count`** (e.g., end of file, partial read).
- On end of file ([[EOF]]): returns 0.
- On error: returns -1 and sets [[errno]].
	- **`EBADF`** → `fd` is not valid or not open for reading.
	- **`EFAULT`** → `buf` is outside accessible memory.
	- **`EINTR`** → Call was interrupted by a signal before reading.
	- **`EAGAIN` / `EWOULDBLOCK`** → Non-blocking I/O, and no data available.
	- **`EINVAL`** → `fd` is unsuitable for reading or `count` is invalid.
	- **`EIO`** → Low-level I/O error occurred.