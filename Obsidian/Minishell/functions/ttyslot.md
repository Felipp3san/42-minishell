https://man7.org/linux/man-pages/man3/ttyslot.3.html

==OBSOLETE==

The `ttyslot` function **returns the index of the current process’s controlling terminal in the system’s terminal database (typically `/etc/ttys` or `/etc/ttytab`)**. This index can then be used by programs (such as login or who) to identify which terminal line the process is running on.

___
## Prototype

```c
#include <unistd.h>

int ttyslot(void);
```

____
## Example

```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int slot = ttyslot();

    if (slot == 0) {
        printf("No terminal slot found.\n");
    } else {
        printf("Terminal slot index: %d\n", slot);
    }

    return 0;
}
```

___
## Return

- **Index number (>= 1)** → The slot number of the controlling terminal.
- **0** → No terminal slot could be found.