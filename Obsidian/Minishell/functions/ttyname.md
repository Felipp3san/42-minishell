https://man7.org/linux/man-pages/man3/ttyname.3.html

The `ttyname` function **returns the pathname of the terminal device** that is associated with a given file descriptor. It is often used together with [[isatty]] to identify which terminal is connected to `stdin`, `stdout`, or `stderr`.

___
## Prototype

```c
#include <unistd.h>

char *ttyname(int fd);
```

___
## Parameters

- **`fd`**: The file descriptor referring to a terminal (e.g., `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO`).

____
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    char *terminal;

    if (isatty(STDIN_FILENO)) {
        terminal = ttyname(STDIN_FILENO);
        if (terminal != NULL) {
            printf("Standard input is connected to terminal: %s\n", terminal);
        } else {
            perror("ttyname failed");
        }
    } else {
        printf("Standard input is not a terminal.\n");
    }

    return 0;
}
```

___
## Return

- **Pointer to a string** → The pathname of the terminal device associated with `fd` (`"/dev/pts/0"`).
- **NULL** → On error, and [[errno]] is set:
    - **`EBADF`** → `fd` is not a valid file descriptor.
    - **`ENOTTY`** → `fd` is not associated with a terminal device.