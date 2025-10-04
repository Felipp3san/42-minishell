https://man7.org/linux/man-pages/man3/strerror.3.html

`strerror` is a function in C that takes an error number ([[errno]]) and returns a human-readable string describing the error. It’s often used for debugging or reporting errors in a user-friendly way.

The string returned by `strerror` **points to static memory managed by the system**, so you **must not free it**. Modifying or freeing it can cause undefined behavior.

___
## Prototype

```c
#include <string.h>

char *strerror(int errnum);
```

___
## Parameters

- **`errnum`**: An integer representing an error code, usually set by system calls or library functions in the global variable [[errno]].

___
## Example

```c
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (!file) {
        printf("Error opening file: %s\n", strerror(errno));
    }
    return 0;
}
```

___
## Return

- A pointer to a string describing the error. The string should **not** be modified or freed by the program.