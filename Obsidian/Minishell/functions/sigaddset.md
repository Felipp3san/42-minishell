https://man7.org/linux/man-pages/man3/sigaddset.3p.html

The `sigaddset` function **adds a specific signal to a signal set**. This is commonly used after initializing a `sigset_t` with [[sigemptyset]] (or `sigfillset`) when you want to manipulate which signals are included in the set.

___
## Prototype

```c
#include <signal.h>

int sigaddset(sigset_t *set, int signum);
```

___
## Parameters

- **`set`**: A pointer to a `sigset_t` variable (the signal set) to which the signal will be added.
- **`signum`**: The signal number (like `SIGINT`, `SIGTERM`, `SIGUSR1`) to add to the set.

___
## Example

```c
#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t set;

    // Initialize empty signal set
    if (sigemptyset(&set) == -1) {
        perror("sigemptyset failed");
        return 1;
    }

    // Add SIGINT to the set
    if (sigaddset(&set, SIGINT) == -1) {
        perror("sigaddset failed");
        return 1;
    }

    // Add SIGTERM to the set
    if (sigaddset(&set, SIGTERM) == -1) {
        perror("sigaddset failed");
        return 1;
    }

    printf("SIGINT and SIGTERM added to the signal set.\n");

    return 0;
}
```

___
## Return

- **0** on success
- **-1** on error and [[errno]] is set.
	- **`EINVAL`** → `signum` is not a valid signal number.
	- **`EFAULT`** → `set` points to an invalid memory address.