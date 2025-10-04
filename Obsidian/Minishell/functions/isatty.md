https://www.man7.org/linux/man-pages/man3/isatty.3.html

The `isatty` function **tests whether a given file descriptor refers to a terminal device**. It is typically used to check if input/output streams like `stdin`, `stdout`, or `stderr` are connected to a terminal or redirected to a file/pipe.

___
## Prototype

```c
#include <unistd.h>

int isatty(int fd);
```

___
## Parameters

- **`fd`**: The file descriptor to test (for example, `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO`, or another open file descriptor).

____
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    if (isatty(STDIN_FILENO)) {
        printf("Standard input is a terminal.\n");
    } else {
        printf("Standard input is not a terminal.\n");
    }

    if (isatty(STDOUT_FILENO)) {
        printf("Standard output is a terminal.\n");
    } else {
        printf("Standard output is not a terminal.\n");
    }

    return 0;
}
```

___
## Return

- **1** → If `fd` refers to a terminal.
- **0** → If `fd` does not refer to a terminal. and [[errno]] is set:
    - **`EBADF`** → `fd` is not a valid open file descriptor.
    - **`ENOTTY`** → `fd` is not associated with a terminal device.