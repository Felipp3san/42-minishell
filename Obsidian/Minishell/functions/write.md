https://man7.org/linux/man-pages/man2/write.2.html

`write` writes up to _count_ bytes from the buffer starting at _buf_ to the file referred to by the file descriptor _fd_

___
## Prototype

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

___
## Parameters

- **`fd`**: File descriptor to write to:
	* **`0`** → stdin (usually not used for writing)
	* **`1`** → stdout (terminal output)
	* **`2`** → stderr
	* Any file descriptor returned by open.
- **`buf`**: Pointer to the buffer containing the data to write.
- **`count`**: Number of bytes to write from the buffer.

___
## Example

**Writing to stdout**
```c
#include <unistd.h>
#include <string.h>

int main() {
    const char *msg = "Hello, world!\n";
    write(1, msg, strlen(msg));  // write to stdout
    return 0;
}
```

**Writing to a file**
```c
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) return 1;

    const char *text = "This is a test\n";
    write(fd, text, 15);  // write 15 bytes to file
    close(fd);
    return 0;
}
```

___
### Return

- On success, the number of bytes written is returned.  
- On error, -1 is returned, and [[errno]] is set to indicate the error.