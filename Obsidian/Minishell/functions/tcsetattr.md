https://man7.org/linux/man-pages/man3/tcsetattr.3p.html

The `tcsetattr` function **sets the parameters of a terminal associated with a file descriptor**. It is commonly used to change terminal attributes such as input/output modes, echoing, and special control characters.

___
## Prototype

```c
#include <termios.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

___
## Parameters

- **`fd`**: File descriptor referring to a terminal (e.g., `STDIN_FILENO`, `STDOUT_FILENO`).
- **`optional_actions`**: When the changes take effect. Possible values:
    - **`TCSANOW`** → The change occurs immediately.
    - **`TCSADRAIN`** → The change occurs after all output written to `fd` has been transmitted.
    - **`TCSAFLUSH`** → The change occurs after transmitting queued output and discarding any unread input.
- **`termios_p`**: Pointer to a `struct termios` containing the new terminal attributes.
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

    // Disable echo
    t.c_lflag &= ~ECHO;

    // Apply the changes immediately
    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1) {
        perror("tcsetattr failed");
        return 1;
    }

    printf("Echo disabled. Type something: ");
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    printf("\nYou typed: %s\n", buf);

    // Restore terminal to original settings (optional)
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    return 0;
}
```

___
## Return

- **0** → On success.
- **-1** → On error, and [[errno]] is set:
    - **`EBADF`** → `fd` is not a valid file descriptor.
    - **`ENOTTY`** → `fd` is not associated with a terminal device.
    - **`EINVAL`** → Invalid `optional_actions` value.