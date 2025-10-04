https://man7.org/linux/man-pages/man2/execve.2.html

`execve` executes the program referred to by _pathname_.  This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

___
## Prototype

```c
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);
```

___
## Parameters

- **`pathname`**: Path to the executable (e.g., /bin/ls).
- **`argv[]`**: Argument vector, with:
	- argv[0] → usually being the program name.
	- Last element → must be NULL.
- **`envp[]`**: Environment variables array, also NULL-terminated (you can pass the global **`environ`** variable).
 ___

## Example

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int main(void) {
    char *argv[] = {"/bin/ls", "-l", NULL};

    if (execve("/bin/ls", argv, environ) == -1) {
        perror("execve failed");
        exit(1);
    }

    // This line is never reached if execve succeeds
    printf("This will not print\n");
    return 0;
}

```

___
## Return

- **On success** → Never returns. The current process memory is replaced.
- **On failure** → Returns `-1` and sets [[errno]].
    - `ENOENT` → File does not exist
    - `EACCES` → Permission denied
    - `ENOMEM` → Not enough memory