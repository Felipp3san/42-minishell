https://tiswww.case.edu/php/chet/readline/readline.html#Miscellaneous-Functions

- Clears the entire history list that [[readline]] maintains internally.
- After calling this, all previously entered commands disappear.
- Useful if you want to reset or limit memory usage.

___
## Prototype

```c
#include <readline/readline.h>
#include <readline/history.h>

void rl_clear_history(void);
```

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char *input;

    while (1) {
        input = readline("myshell> ");
        if (!input) {
            break;  // EOF (Ctrl+D)
        }

        // if user typed something, store in history
        if (*input) {
            add_history(input);
        }

        // clear history if user types "clearhist"
        if (strcmp(input, "clearhist") == 0) {
            rl_clear_history();
            printf("History cleared!\n");
        }

        // exit if user types "exit"
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        free(input);
    }

    return 0;
}
```

___
## Return

- The function does not return anything.