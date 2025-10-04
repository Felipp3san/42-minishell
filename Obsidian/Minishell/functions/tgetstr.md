The **`tgetstr`** function retrieves the string capability associated with a given capability name from the terminal description (previously loaded by [[tgetent]]).

These string capabilities often represent control sequences used to perform terminal actions, such as moving the cursor, clearing the screen, or setting display attributes.

___
## Prototype

```c
#include <curses.h>
#include <term.h>

char *tgetstr(const char *id, char **area);
```

___
## Parameters

- **`id`**: A two-character string identifying the capability to retrieve.  
    Example capabilities:    
    - `"cl"` → clear screen
    - `"cm"` → cursor motion
    - `"so"` → enter standout mode
- **`area`**: A pointer to a character pointer used as storage for the returned capability string.
    - If not `NULL`, the capability string is copied into the buffer pointed to by `*area`, and `*area` is advanced past the copied string.
    - If `NULL`, the function returns a pointer to a static area (not re-entrant).

___
## Compilation

To use `tgetent`, you must link against the **curses** library. 
On most systems, the command looks like:

```bash
cc main.c -lncurses -o myprog
```

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int main(void) {
    char term_buffer[2048];
    char *termtype = getenv("TERM");
    char *area = term_buffer;
    
    if (tgetent(term_buffer, termtype) != 1) {
        fprintf(stderr, "Could not load terminal type %s\n", termtype);
        return 1;
    }

    char *cl = tgetstr("cl", &area);
    if (cl == NULL) {
        fprintf(stderr, "Clear screen capability not found.\n");
        return 1;
    }

    // Use tputs to send the sequence to the terminal
    tputs(cl, 1, putchar);

    return 0;
}
```

___
## Return

- On **success**: returns a pointer to the string capability for the given identifier.
- On **failure**: returns `NULL` if the capability does not exist for the terminal.: