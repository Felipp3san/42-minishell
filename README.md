# Minishell

A fully functional **Unix shell** built in **C**, designed to mimic the behavior of **Bash** while reinforcing knowledge of process management, pipes, signals, and parsing.
It provides a complete interactive shell experience with built-in commands, environment handling, and robust execution flow.

## Features

- **Interactive prompt** for executing commands  
- **Built-in commands**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`  
- **Pipes** (`|`) and **redirections** (`<`, `>`, `>>`, `<<`)  
- **Environment variable expansion** (e.g. `$USER`, `$PATH`)  
- **Signal handling** for `Ctrl + C`, `Ctrl + D`, and `Ctrl + \`  
- **Error messages** consistent with Bash  
- **Memory-safe execution** (no leaks, fully cleaned after exit)  

## Tech Stack

- **C** – Core language  
- **GNU Readline** – For interactive input
- **POSIX system calls** – `fork`, `execvp`, `pipe`, `dup2`, `wait`, `signal`, etc.  
- **Makefile** – For easy build and management

## Installation

1. Clone the repository:

```bash
git clone https://github.com/Felipp3san/42-minishell
cd 42-minishell
```

2. Compile the project:

```bash
make
```

3. Run the executable:

```bash
./minishell
```

## Usage

- **Run commands** just like in Bash:

```bash
minishell$ ls -l | grep minishell
```

- **Set and use environment variables:**

```bash
minishell$ export NAME=Felippe
minishell$ echo "Hello $NAME"
Hello Felippe
```

- **Redirect input and output:**

```bash
minishell$ cat < input.txt | grep "data" > output.txt
```

- **Exit the shell:**

```bash
minishell$ exit
```

## Compilation

- Build the executable:

```bash
make
```

- Remove object files:

```bash
make clean
```

- Remove all binaries and rebuild:

```bash
make re
```

## Project Structure

```
.
├── include/             # Header files
├── src/                 # Source files
│    ├── builtins/       # Built-in shell commands
│    ├── command/        # Command structures
│    ├── debug/          # Debugging utilities
│    ├── env/            # Environment variable management
│    ├── executor/       # Command executor logic
│    ├── expander/       # Variable and wildcard expansion
│    ├── heredoc/        # Here-document handling
│    ├── parser/         # Parsing logic for commands
│    ├── path/           # Path resolution and management
│    ├── signals/        # Signal handling (e.g., SIGINT)
│    ├── token/          # Token structures
│    ├── tokenizer/      # Lexical analysis
│    ├── ui/             # User interface components
│    ├── utils/          # Utility functions
│    └── main.c          # Program entry point
└── libft/               # Custom Libft library
```

## License

Educational project under 42 School academic policy.
