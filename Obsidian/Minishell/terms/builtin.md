In a shell (bash, zsh, etc.), a **builtin command** is one that is **implemented directly inside the shell program**, not as a separate binary (`/bin/ls`, `/usr/bin/grep`, etc.).

- Handled by the shell itself (no [[fork]] unless inside a pipeline).
___

- **Builtin**: handled by the shell itself (no [[fork]] unless inside a pipeline).

```bash
shell> cd ..
# the shell itself changes directory
```

- **External command**: located somewhere in the filesystem (like `/bin/ls`), launched using [[fork]] + [[execve]].

```bash
shell> ls
# shell forks a child, runs /bin/ls
```

___
- Some builtins **must run in the current shell process**, not in a child:
	[[cd]], [[export]], [[unset]], [[exit]]

- Others can run in a child if convenient:
	[[echo]], [[pwd]], [[env]]