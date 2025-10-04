https://man7.org/linux/man-pages/man3/free.3p.html

The `free` function shall cause the space pointed to by ptr to be deallocated; that is, made available for further allocation. If ptr is a null pointer, no action shall occur.

___
## Prototype

```c
#include <stdlib.h>

void free(void *ptr);
```

___
## Parameters

- **`ptr`**:  Pointer to a memory block previously allocated by [[malloc]], `calloc`, or `realloc`.

___
## Example

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for an array of 5 integers
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Fill the array
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr);

    // After freeing, arr pointer is dangling; safe practice is to set it to NULL
    arr = NULL;

    return 0;
}

```

___
## Return

- The function does not return anything.