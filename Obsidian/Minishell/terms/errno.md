https://man7.org/linux/man-pages/man3/errno.3.html

```c
#include <errno.h>
```

**`errno`** is a **global variable** that the system uses to indicate the error status of the last library or system call.

The _<errno.h>_ header file defines the integer variable _errno_, which is set by system calls and some library functions in the event of an error to indicate what went wrong.

___
## Example

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("nonexistent.txt", "r"); // this will fail
    if (fp == NULL) {
        printf("Error opening file: %s\n", strerror(errno));
    }
    return 0;
}
```

___
### Common Error Codes (`errno.h`):

- `EACCES` – Permission denied
- `ENOENT` – No such file or directory
- `ENOMEM` – Out of memory
- `EINTR` – Interrupted system call