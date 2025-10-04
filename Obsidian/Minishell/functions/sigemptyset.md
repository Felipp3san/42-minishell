https://man7.org/linux/man-pages/man3/sigemptyset.3p.html

The `sigemptyset` function initializes a signal set to **exclude all signals**. After calling this function, the signal set contains **no signals**. It is commonly used before adding specific signals to the set with [[sigaddset]].

___
## Prototype

```c
#include <signal.h>

int sigemptyset(sigset_t *set);
```

___
## Parameters

- **`set`**: A pointer to a `sigset_t` variable (a signal set) that will be initialized.

___
## Example

```c
#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t set;

    if (sigemptyset(&set) == -1) {
        perror("sigemptyset failed");
        return 1;
    }

    // Now `set` contains no signals, ready for sigaddset() or sigprocmask()
    printf("Signal set initialized and empty.\n");

    return 0;
}
```

**using an initialized set**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nCaught SIGINT (%d)!\n", sig);
}

int main() {
    struct sigaction sa;
    sigset_t set;

    // Initialize the signal set to be empty
    if (sigemptyset(&set) == -1) {
        perror("sigemptyset failed");
        return 1;
    }

    // Add SIGTERM to the set of signals to block during the handler
    if (sigaddset(&set, SIGTERM) == -1) {
        perror("sigaddset failed");
        return 1;
    }

    // Set up the sigaction struct
    sa.sa_handler = handle_sigint;  // Handler function for SIGINT
    sa.sa_mask = set;               // Signals to block during handler
    sa.sa_flags = 0;

    // Apply the sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction failed");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT. SIGTERM is blocked during handler.\n");

    // Wait indefinitely
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
```

___
## Notes

- Always initialize a `sigset_t` before using it in functions like [[sigaddset]], `sigprocmask`, or `sigsuspend`.
- `sigemptyset` **does not block signals**; it just prepares an empty set. You need other functions to modify the signal mask.

___
## Return

- **0** on success
- **-1** on error, and [[errno]] is set.
	- **`EFAULT`** → `set` points to an invalid memory address.