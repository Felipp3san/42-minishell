https://tiswww.case.edu/php/chet/readline/readline.html#Redisplay

- Tells [[readline]] that you’ve moved to a new line.
- Normally used before redrawing the current input line (e.g., after printing something asynchronously, like a signal handler printing a message).
- It doesn’t print anything by itself—just updates internal state.

___
## Prototype

```c
#include <readline/readline.h>

int rl_on_new_line(void);
```

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum) {
	// Avoid compiler warning (unused variable)
    (void)signum;

    // Print a message safely
    write(STDOUT_FILENO, "\nCaught SIGINT\n", 15);

    // Tell readline we’re on a new line and refresh the prompt
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(void) {
    char *input;

    // Install handler
    signal(SIGINT, sigint_handler);

    while (1) {
        input = readline("myshell> ");
        if (!input) {
            break; // EOF (Ctrl+D)
        }

        if (*input) {
            add_history(input);
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        printf("You typed: %s\n", input);
        free(input);
    }

    return 0;
}
```

___
## Return

- Always returns 0, It doesn’t fail under normal circumstances; the return value is mostly unused in practice.