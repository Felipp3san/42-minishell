https://man7.org/linux/man-pages/man3/perror.3.html

`perror` prints a **human-readable error message** to `stderr` based on the current value of [[errno]], optionally prefixed by a custom string. It’s convenient when you want to report an error without manually calling [[strerror]].

convenient alternative to:
```c
fprintf(stderr, "%s: %s\n", msg, strerror(errno));
```

___
## Prototype

```c
#include <stdio.h>

void perror(const char *s);
```

___
## Parameters

- **`s`**: A string you provide, usually the name of the operation that failed. Can be `NULL`.
	- Writes to `stderr` the string `s`, followed by `": "`, followed by the textual description of the current `errno`, ending with a newline.

___
## Example

```c
#include <stdio.h>
#include <errno.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    if (!file) {
        perror("fopen failed");
    }
    return 0;
}
```

___
## Return

- The function does not return anything.