- Tokens are not enough; you need to build a structure (AST or a command tree).  

- Example:
```bash
ls -l | grep txt > out.txt
```

- Becomes something like:
```nginx
PIPE
 ├── COMMAND "ls" ["-l"]
 └── REDIR ">" "out.txt"
     └── COMMAND "grep" ["txt"]