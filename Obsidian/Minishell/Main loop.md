### 1. **Check for special cases**

- If the string is `NULL` → user pressed `Ctrl+D` ([[EOF]]). That usually means you should exit the shell.
- If the string is empty (just `Enter`) → ignore it and prompt again.

___
### 2. **History management (optional but common)**

- If the line is non-empty, you can `add_history(input)` so the user can navigate it with ↑ ↓ keys.