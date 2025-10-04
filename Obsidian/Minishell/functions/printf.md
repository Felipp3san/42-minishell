https://man7.org/linux/man-pages/man3/printf.3.html

`printf` writes formatted output to the standard output stream (`stdout`).  It interprets a **format string** and replaces conversion specifiers (e.g., `%d`, `%s`, `%f`) with the corresponding values passed as additional arguments.  

It is part of the standard C library and is widely used for displaying text, numbers, and formatted data.

___
## Prototype

```c
#include <stdio.h>

int printf(const char *format, ...);
```

___
## Parameters

- **`format`**:  Format string that specifies how output is written:
    - Contains ordinary characters (printed as-is).
    - Contains conversion specifiers starting with `%` (e.g., `%d`, `%s`, `%f`) that define how to interpret the following arguments.
    - Supports flags (`-`, `+`, `0`, etc.), width, precision, and length modifiers.
- **`...` (variadic arguments)**:  Values to print, matched in order with the conversion specifiers in `format`.
    - Example:
        - `%d` → expects `int`
        - `%ld` → expects `long int`
        - `%f` → expects `double`
        - `%s` → expects `char *` (C string)
        - `%c` → expects `int` (character)

___
## Example

```c
#include <stdio.h>

int main(void) {
    int x = 42;
    const char *str = "hello";

    int written = printf("Number: %d, Text: %s\n", x, str);

    if (written < 0) {
        perror("printf error");
        return 1;
    }

    printf("Characters printed: %d\n", written);
    return 0;
}
```

___
## Notes

- Output is written to **`stdout`**.
- To print to other streams, use fprintf.
- To format text into a string instead of printing, use sprintf / snprintf.
- Since it’s variadic, type mismatches between the format specifiers and provided arguments cause undefined behavior.

___
## Return

- On **success**: returns the **number of characters written** (not counting the null terminator).
- On **failure**: returns a **negative value** and [[errno]] is set to indicate the error. Common `errno` values:
	- **`EIO`** → Error writing to the output stream.
	- **`EOVERFLOW`** →The value to be returned is greater than **INT_MAX**.
	- **`EINVAL`** → Invalid format string or unsupported specifier.