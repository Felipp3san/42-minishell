https://tiswww.case.edu/php/chet/readline/history.html#History-List-Management

- Adds the given string to the [[readline]] history list.
- Without calling this, `↑` / `↓` won’t cycle through previously typed commands.
- Commonly used right after [[readline]] if the user typed something non-empty.

___
## Prototype

```c
#include <readline/readline.h>
#include <readline/history.h>

void add_history(const char *line);
```

___
## Parameters

- **`line`**: A pointer to a null-terminated string (the most recent input returned by [[readline]]) that you want to add to the history list. Only non-empty strings are typically stored.

___
## Example

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    while (1)
    {
        // Read a line from the user
        input = readline("myshell> ");

        if (!input)
            break; // Ctrl+D exits

        if (*input) // Only add non-empty lines to history
            add_history(input);

        printf("You typed: %s\n", input);

        free(input); // readline allocates memory, so we must free it
    }

    return 0;
}
```

___
## Return

- The function does not return anything.