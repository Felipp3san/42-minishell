https://man7.org/linux/man-pages/man2/sigaction.2.html

The `sigaction` function is used to **examine or change the action associated with a specific [[terms/signal|signal]].
- It replaces the old signal handler for the signal `signum` with the new one defined in `act`.
- The previous action can optionally be saved in `oldact`.
- Preferred over the older [[functions/signal|signal]] function because it is **more reliable and portable**, especially regarding restarting system calls and signal flags.

____
## Prototype

```c
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

___
## Parameters

- **`signum`**: The signal number to handle (e.g., `SIGINT`, `SIGTERM`, `SIGUSR1`).
- **`act`**:  Pointer to a `struct sigaction` describing the new action. If `NULL`, the signal action is **not changed**.
- **`oldact`**:  Pointer to a `struct sigaction` to store the previous action. Can be `NULL` if you don’t care.
### struct sigaction

```c
struct sigaction {
    void (*sa_handler)(int);   // Function pointer to signal handler
    sigset_t sa_mask;          // Signals to block during handler execution
    int sa_flags;              // Flags to modify behavior (e.g., SA_RESTART)
    void (*sa_sigaction)(int, siginfo_t *, void *); // Alternative handler (used with SA_SIGINFO)
};
```

- **`sa_handler`** → Basic signal handler function: **`void handler(int sig)`**.
	-  **`SIG_DFL`** for the default action.
    -  **`SIG_IGN`** to ignore this signal.
- **`sa_mask`** → Signals blocked while this handler runs.
- **`sa_flags`** → Modify behavior:
	- **`SA_RESTART`** → Automatically restart certain interrupted system calls.
	- **`SA_SIGINFO`** → Use sa_sigaction instead of sa_handler.
- **`sa_sigaction`** → More advanced handler with extra info (siginfo_t).

___
## Example

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT...\n");
    while (1) {
        sleep(1);
    }

    return 0;
}
```

___
## Return

- **Success:** returns `0`.
- **Failure:** returns `-1` and sets [[errno]].
	- **`EINVAL`** → Invalid signal number or invalid flags in `sa_flags`. 
		- This will also be generated if an attempt is made to change the action for **SIGKILL** or **SIGSTOP**, which cannot be caught or ignored.
	- **`EFAULT`** → `act` or `oldact` points to invalid memory.