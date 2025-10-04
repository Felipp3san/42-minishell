https://www.man7.org/linux/man-pages/man3/readline.3.html
https://tiswww.case.edu/php/chet/readline/readline.html

`readline` reads a line from the terminal and return it, using **prompt** as a prompt.  If **prompt** is **NULL** or the empty string, **readline** does not issue a prompt.  The line returned is allocated with [[malloc]] the caller must free it when finished.

- Displays a prompt string (e.g. `"minishell> "`).
- Reads an entire line of user input, allowing editing (arrows, backspace, etc.).
- Returns the line as a dynamically allocated  `char*` (you must [[free]] it).
- Returns `NULL` if [[EOF]] is reached (e.g., user pressed `Ctrl+D`).

___
## Prototype

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);
```

___
## Parameters

- **`prompt`**: A string shown to the user before waiting for input (e.g., `"minishell$ "`).
    - If `prompt` is `NULL`, nothing is displayed.

___
## Compilation

To use `readline`, you must link against the **readline** library.  
On most systems, the command looks like:

```bash
cc main.c -lreadline -o myprog
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
        input = readline("minishell$ ");  // show prompt

        if (!input) {  // user pressed Ctrl+D (EOF)
            printf("exit\n");
            break;
        }

        if (*input) {  // if not empty string
            add_history(input);  // saves command in history
        }

        printf("You typed: %s\n", input);

        free(input);  // free memory allocated by readline
    }

    return 0;
}
```

___
## Features 

- **Line editing**: move cursor with arrows, delete characters, etc.
- **History support**: recall previous commands with ↑ ↓.
- **Auto-completion**: can be configured.
- Removes the trailing `\n`, unlike `fgets`.

___
## Return

- Returns a **dynamically allocated string** containing the user’s input (without the trailing newline).
- Returns **`NULL`** if:
    - [[EOF]] (Ctrl+D) is encountered.
    - An error occurs.

**Since the return is dynamically allocated, you must [[free]] it when you’re done.**