https://man7.org/linux/man-pages/man3/getcwd.3.html

`getcwd` return a null-terminated string containing an absolute path name that is the current working directory of the calling process.  
The path name is returned as the function result and via the argument _buf_, if present.
   
___
## Prototype

```c
#include <unistd.h>

char *getcwd(char *buf, size_t size);
```

___
## Parameters

- **`buf`**: A pointer to a character array where `getcwd` will store the path.
    - If `buf` is `NULL`, `getcwd` will allocate memory dynamically using [[malloc]].
- **`size`**: The size of the buffer `buf` in bytes.
    - Ignored if `buf` is `NULL`.
    - If the path is longer than `size`, `getcwd` fails and sets [[errno]] to **`ERANGE`**.

___
## Example

**Using fixed buffer**
```c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }

    return 0;
}
```

**Using `NULL` for automatic allocation**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *cwd;
    
    cwd = getcwd(NULL, 0); // allocates enough memory automatically
    
    if (cwd != NULL) {
        printf("Current working directory: %s\n", cwd);
        free(cwd); // free the memory allocated by getcwd
    } else {
        perror("getcwd() error");
    }

    return 0;
}
```

___
## Return

- **Success:**
	- Returns **the same pointer you passed** (`buf`), containing the path.
	    - if **`buf`** is **`NULL`** `getcwd` allocates memory dynamically using [[malloc]], then it returns a pointer to the allocated string, which you must free when done.
-  **Failure:**
    - Returns **`NULL`**.
    - Sets `errno` to indicate the error:
        - `ERANGE` → buffer too small for the current path
        - `EACCES` → permission denied
        - `ENOENT` → current directory no longer exists