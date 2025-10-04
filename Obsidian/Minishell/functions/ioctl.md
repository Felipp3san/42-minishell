https://man7.org/linux/man-pages/man2/ioctl.2.html

The `ioctl` function **performs device-specific input/output operations on file descriptors**. It provides a way to control underlying devices (like terminals, sockets, and special files) that cannot be managed using regular system calls such as [[read]] or [[write]]. Its behavior depends on the **request code** and optional **argument** passed.

___
## Prototype

```c
#include <sys/ioctl.h>

int ioctl(int fd, unsigned long request, ...);
```

___
## Parameters

- **`fd`**: File descriptor referring to the open device (e.g., terminal, socket, block device).
- **`request`**: The control command (an operation code defined in headers such as `<termios.h>` or device-specific headers).
- **`...`**: An optional third argument, usually a pointer to memory (struct or variable) containing data to send or receive, depending on the request.

____
## Example

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void) {
    int rows, cols;

    // Get the terminal window size
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl failed");
        return 1;
    }

    rows = w.ws_row;
    cols = w.ws_col;

    printf("Terminal size: %d rows, %d columns\n", rows, cols);

    return 0;
}
```

___
## Return

- **0** → On success for many requests.
- **-1** → On error, and [[errno]] is set appropriately.
    - **`EBADF`** → `fd` is not a valid open file descriptor.
    - **`ENOTTY`** → The file descriptor is not associated with a terminal device, or the request is inappropriate for the device.
    - **`EINVAL`** → Invalid request code or argument.

___
## Requests

#### 1. **Terminal Control (`<termios.h>` / `<sys/ioctl.h>`)**

- **`TIOCGWINSZ`** → Get terminal window size (`struct winsize`).
- **`TIOCSWINSZ`** → Set terminal window size (`struct winsize`).
- **`TCGETS`** → Get terminal attributes (termios struct).
- **`TCSETS`** → Set terminal attributes.
- **`TIOCGETA` / `TIOCSETA`** → Alternative names for getting/setting termios attributes.
- **`TIOCSTI`** → Insert characters into terminal input buffer (like simulating typing).
- **`TIOCSPGRP` / `TIOCGPGRP`** → Set / Get foreground process group of a terminal.
- **`TIOCGSID`** → Get session ID of terminal.
#### 2. **File Descriptors / Device I/O**

- **`FIONBIO`** → Enable or disable non-blocking mode on a file descriptor.
- **`FIONREAD`** → Get the number of bytes available to read.
- **`FIOASYNC`** → Enable or disable asynchronous I/O notification (SIGIO).
#### 3. **Sockets / Networking**

- **`SIOCGIFADDR`** → Get IP address of a network interface.
- **`SIOCSIFADDR`** → Set IP address of a network interface.
- **`SIOCGIFMTU`** → Get MTU (Maximum Transmission Unit) of interface.
- **`SIOCSIFMTU`** → Set MTU.
- **`SIOCGIFFLAGS` / `SIOCSIFFLAGS`** → Get / Set interface flags (up, broadcast, etc.).
- **`SIOCGIFHWADDR`** → Get MAC (hardware) address.
#### 4. **Block Devices / Storage**

- **`BLKGETSIZE`** → Get device size in 512-byte sectors.
- **`BLKSSZGET`** → Get logical block size.
- **`BLKROSET` / `BLKROGET`** → Set / Get read-only status.
#### 5. **Miscellaneous**

- **`TIOCMGET` / `TIOCMSET`** → Get / Set modem control lines (DTR, RTS).
- **`TIOCGSERIAL` / `TIOCSSERIAL`** → Get / set serial port parameters.
- **`KDGETMODE` / `KDSETMODE`** → Kernel console mode (text / graphics).