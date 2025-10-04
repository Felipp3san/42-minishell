The **`tputs`** function outputs a terminal control string (usually obtained with [[tgetstr]]) to the terminal.  
It processes padding information embedded in the string (if the terminal requires delays) and sends the control sequence character by character using a callback function.

This is the **standard way** to apply terminal capability strings like _clear screen_, _cursor move_, or _highlight mode_.

___
## Prototype

```c
#include <curses.h>    // or <term.h> depending on system

int tputs(const char *str, int affcnt, int (*putc)(int));
```

___
## Parameters

- **`str`** →  
    The control string to output (usually from `tgetstr`).  
    Example: the sequence for clearing the screen (`cl` capability).
- **`affcnt`** →  
    The number of lines affected by the operation (used when calculating padding).
    - If the capability does not involve multiple lines, pass **1**.
    - Example: for `clear screen`, you can just pass `1`.
- **`putc`** →  
    A pointer to a function used to output each character.
    - Commonly you pass `putchar`.
    - Must accept an `int` (the character) and return an `int`.

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
#include <curses.h>
#include <term.h>

int main(void) {
    char *termtype = getenv("TERM");
    if (termtype == NULL) {
        fprintf(stderr, "TERM not set.\n");
        return 1;
    }

    if (tgetent(NULL, termtype) != 1) {
        fprintf(stderr, "Could not load terminal type %s.\n", termtype);
        return 1;
    }

    char *clear = tgetstr("cl", NULL);
    if (clear == NULL) {
        fprintf(stderr, "No 'cl' capability for this terminal.\n");
        return 1;
    }

    // Output clear screen sequence using tputs
    tputs(clear, 1, putchar);

    return 0;
}
```

___
## Return

- **`OK` (usually 0)** → Success.
- **`ERR` (usually -1)** → Failure (invalid string or output error).