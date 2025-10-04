https://tiswww.case.edu/php/chet/readline/readline.html#Modifying-Text

- Replaces the current contents of the input buffer (the line the user is editing) with `text`.
- If `clear_undo` is nonzero, it also clears the undo list (so user can’t undo back to old line).

==[[rl_replace_line]] and [[rl_redisplay]] only affect the line buffer while [[readline]] is actively waiting for user input.==
___
## Prototype

```c
#include <readline/readline.h>

void rl_replace_line(const char *text, int clear_undo);
```

____
## Parameters

- **`text`**: String to replace the current line.
- **`clear_undo`**: `0` to **not save the old line for undo**, `1` to save it for undo.

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

___
## Return

- The function does not return anything.
void sigint_handler(int sig) {
	// Avoid compiler warning (unused variable)
    (void)sig;

    // Move to a new line before printing
    rl_on_new_line();

    // Print message using printf
    printf("\nCtrl+C pressed!\n");

    // Replace current input with a custom line
    rl_replace_line("You can't type now!", 0);

    // Redisplay prompt and new line
    rl_redisplay();
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