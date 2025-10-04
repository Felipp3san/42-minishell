https://man7.org/linux/man-pages/man5/termcap.5.html
https://man7.org/linux/man-pages/man3/curs_termcap.3x.html

Before **terminfo** and libraries like **ncurses**, applications relied on **termcap** to figure out how to control the terminal (move the cursor, clear the screen, change text style, etc.) in a **terminal-independent way**.

Instead of hardcoding escape sequences (like `"\033[2J"` to clear the screen), programs asked termcap:
- “How do I clear the screen on _this_ terminal?”
- “How do I move the cursor to row X, col Y?”

The answers came from the **termcap database** (`/etc/termcap` or similar), which describes capabilities of different terminal types.

---

### Functions overview

- [[tgetent]]
    Loads the terminal description for `name` (usually from the `TERM` environment variable) into the buffer `bp`.  
    This must be called **first**.

- [[tgetflag]]
    Gets a boolean capability (yes/no). Example: whether the terminal supports auto-margins.

- [[tgetnum]]
    Gets a numeric capability. Example: the number of columns (`co`) or lines (`li`) in the terminal.

- [[tgetstr]]
    Gets a string capability (usually an escape sequence). Example: the string to clear the screen (`cl`) or move the cursor home (`ho`).

- [[tgoto]]
    Processes a cursor movement capability string (`cm`) returned by `tgetstr`, replacing placeholders with the given row/column values.

- [[tputs]]
    Outputs a capability string (like the one returned by [[tgetstr]] or [[tgoto]]) to the terminal, handling padding/delays if needed.  
    You provide a function (like `putchar`) to actually send each character.