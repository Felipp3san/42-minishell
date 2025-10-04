https://tiswww.case.edu/php/chet/readline/readline.html#Redisplay

- Redraws the current input line on the terminal.
- Typically used after [[rl_replace_line]] or when something external has messed up the display (like printing logs while typing).

==[[rl_replace_line]] and [[rl_redisplay]] only affect the line buffer while [[readline]] is actively waiting for user input.==
___
## Prototype

```c
#include <readline/readline.h>

void rl_redisplay(void);
```

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void sigint_handler(int sig) {
    (void)sig;
    
    rl_replace_line("You pressed Ctrl+C!", 1); // Replace current editing line
    rl_redisplay();                     // Redraw prompt with replaced line
}

int main(void) {
    char *input;

    signal(SIGINT, sigint_handler);

    while ((input = readline("myshell> ")) != NULL) {
        if (*input)
            add_history(input);

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

- The function does not return anything.