https://man7.org/linux/man-pages/man2/signal.2.html

The `signal` function is used to **set up a signal handler** — that is, to tell the program what to do when it receives a particular signal (like `SIGINT` when you press **Ctrl+C**).

==For portable, reliable handling, you should prefer [[sigaction]] instead.==
___
## Prototype

```c
#include <signal.h>
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
```

____
## Parameters

- **`signum`**: The signal number (e.g., `SIGINT`, `SIGTERM`, `SIGCHLD`, etc.).
	==The signals **SIGKILL** and **SIGSTOP** cannot be caught or ignored.==
- **`handler`**: A function pointer to your custom handler, which must have the form:
```c
void handler(int signum);
```

___
## Example

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    // Catch SIGINT (Ctrl+C)
    signal(SIGINT, my_handler);

    // Infinite loop so you can test it
    while (1) {
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}
```

___
## Return

- The **previous signal handler** 
- **`SIG_ERR`** on error, and [[errno]] is set to indicate the error.