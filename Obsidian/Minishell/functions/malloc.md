https://man7.org/linux/man-pages/man3/malloc.3.html

The `malloc` function allocates _size_ bytes and returns a pointer to the allocated memory.  _The memory is not initialized_.  If _size_ is 0, then `malloc` returns a unique pointer value that can later be successfully passed to [[free]].

___
## Prototype

```c
#include <stdlib.h>

void *malloc(size_t size);
```

___
## Parameters

- **`size`**:  The **number of bytes** you want to allocate in memory.

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;

    // Allocate memory for n integers
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize and print the array
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;  // example values
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr);

    // Prevent dangling pointer
    arr = NULL;

    return 0;
}
```

___
### Return

The **malloc**() function returns a pointer to the allocated memory, which is suitably aligned for any type that
fits into the requested size or less. On error, these functions return NULL and set [[errno]].