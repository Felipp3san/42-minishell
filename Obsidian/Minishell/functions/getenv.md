https://man7.org/linux/man-pages/man3/getenv.3.html

The `getenv` function **retrieves the value of an environment variable** from the calling process’s environment. 

___
## Prototype

```c
#include <stdlib.h>

char *getenv(const char *name);
```

___
## Parameters

- **`name`**: A null-terminated string containing the name of the environment variable to retrieve (e.g., `"HOME"`, `"PATH"`).

____
## Example

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *home = getenv("HOME");
    if (home != NULL) {
        printf("Your home directory is: %s\n", home);
    } else {
        printf("HOME environment variable not found.\n");
    }

    char *path = getenv("PATH");
    if (path != NULL) {
        printf("System PATH: %s\n", path);
    }

    return 0;
}
```

___
## Return

- **Pointer to the value string** → The value of the requested environment variable.
- **NULL** → If the environment variable does not exist.

 ⚠️ Do **not** modify the returned string; it points to memory managed by the system.