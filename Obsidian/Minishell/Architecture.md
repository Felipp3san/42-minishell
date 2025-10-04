
1. **[[Main loop]]**
	- Print prompt, get input, pass to tokenizer/parser/executor.
2. **[[Tokenizer]]**
	- Tokenize input (`ls -l | grep foo > out.txt`)
    - Handle quotes (`" "`, `' '`)
3. **[[Parser]]**
    - Handle variables (`$HOME`, `$?`)
    - Build a command structure (`cmd`, `args[]`, `in/out files`, `pipe`)
4. **[[Executor]]**
    - Decide if it’s a [[builtin]] or **external**
    - Handle redirections & pipes
	    - **`<`**: should redirect input. 
	    - **`>`**: should redirect output. 
	    - **`<<`**: should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history! 
	    - **`>>`**: should redirect output in append mode.
    - [[fork]] + [[execve]] if external
5. **[[builtin]]**
    - Implement one by one: [[cd]], [[echo]], [[pwd]], etc.
    - List of mandatory [[builtin]] in 42 minishell
		- [[echo]] (with `-n` option)
		- [[cd]]
		- [[pwd]]
		- [[export]]
		- [[unset]]
		- [[env]]
		- [[exit]]
    - Remember: some must run **inside the current shell process** (like [[cd]], [[export]], [[unset]], [[exit]]).
6. [[terms/signal|signal]]
    - Ignore or handle differently in child vs parent
    - Must behave like bash (`Ctrl-C` cancels input, `Ctrl-D` exits, etc.)
	    -  In parent shell: `Ctrl-C` should **not exit** minishell, just show a new prompt.
		- In child process: `Ctrl-C` should kill the running command.
		- `Ctrl-D`: should **exit** shell if line is empty.