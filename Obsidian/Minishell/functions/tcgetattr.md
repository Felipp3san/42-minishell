https://man7.org/linux/man-pages/man3/tcgetattr.3p.html

The `tcgetattr` function **gets the parameters of a terminal associated with a file descriptor**. It is commonly used to retrieve the current terminal settings so they can be inspected or modified with [[tcsetattr]].

___
## Prototype

```c
#include <termios.h>

int tcgetattr(int fd, struct termios *termios_p);
```

___
## Parameters

- **`fd`**: File descriptor referring to a terminal (e.g., `STDIN_FILENO`, `STDOUT_FILENO`).
- **`termios_p`**: Pointer to a `struct termios` where the current terminal attributes will be stored.
### struct termios

```c
#include <termios.h>

struct termios {
    tcflag_t c_iflag;   // Input modes
    tcflag_t c_oflag;   // Output modes
    tcflag_t c_cflag;   // Control modes
    tcflag_t c_lflag;   // Local modes
    cc_t     c_cc[NCCS]; // Special control characters
};
```

- **`c_iflag`** → Input modes (e.g., `IGNBRK`, `ICRNL`, `IXON`).
- **`c_oflag`** → Output modes (e.g., `OPOST`, `ONLCR`).
- **`c_cflag`** → Control modes (e.g., `CSIZE`, `CSTOPB`, `CREAD`, `CLOCAL`).
- **`c_lflag`** → Local modes (e.g., `ECHO`, `ICANON`, `ISIG`, `IEXTEN`).
- **`c_cc[NCCS]`** → Array of special control characters, indices include:
    - `VINTR` → Interrupt character (usually Ctrl+C)
    - `VQUIT` → Quit character (usually Ctrl+)
    - `VERASE` → Erase character (usually Backspace)
    - `VKILL` → Kill line character
    - `VEOF` → End-of-file character (usually Ctrl+D)
    - `VTIME`, `VMIN` → For non canonical read timing

___
## Example

```c
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void) {
    struct termios t;

    // Get current terminal attributes
    if (tcgetattr(STDIN_FILENO, &t) == -1) {
        perror("tcgetattr failed");
        return 1;
    }

    printf("Current terminal flags:\n");
    printf("  ECHO: %s\n", (t.c_lflag & ECHO) ? "on" : "off");
    printf("  ICANON: %s\n", (t.c_lflag & ICANON) ? "on" : "off");

    return 0;
}
```

___
## Return

- **0** → On success.
- **-1** → On error, and [[errno]] is set:
    - **`EBADF`** → `fd` is not a valid file descriptor.
    - **`ENOTTY`** → `fd` is not associated with a terminal device.