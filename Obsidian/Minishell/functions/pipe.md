https://man7.org/linux/man-pages/man2/pipe.2.html

`pipe` creates a **unidirectional communication channel** (a pipe) between two file descriptors.  Data written to one end of the pipe can be read from the other end.  
Pipes are commonly used for **inter-process communication (IPC)** between a parent and child process after [[fork]].

___
## Prototype

```c
#include <unistd.h>

int pipe(int pipefd[2]);
```

___
## Parameters

- **`pipefd`**: Array of two integers used to return the file descriptors:
    - `pipefd[0]`→ Read end of the pipe.
    - `pipefd[1]`→ Write end of the pipe.

___
## Example

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int pipefd[2];
    char buffer[64];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Write to the pipe
    const char *msg = "Hello through pipe!";
    write(pipefd[1], msg, strlen(msg));

    // Close write end (optional, good practice)
    close(pipefd[1]);

    // Read from the pipe
    ssize_t nbytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
    if (nbytes == -1) {
        perror("read");
        exit(1);
    }
    buffer[nbytes] = '\0';

    printf("Read from pipe: %s\n", buffer);

    close(pipefd[0]);
    return 0;
}
```

___
## Return

- On **success**: returns `0` and fills **`pipefd[0]`** and **`pipefd[1]`**.
- On **failure**: returns `-1`, sets [[errno]] and **`pipefd`** is left unchanged. 
	-  **`EMFILE`** → The process already has too many file descriptors open.
	- **`ENFILE`** → The system file table is full.
	- **`EFAULT`** → **`pipefd`** array is not valid (points to invalid memory).
	- **`ENOMEM`** → Insufficient kernel memory to create the pipe.
