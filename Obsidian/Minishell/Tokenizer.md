
- This means splitting the line into meaningful pieces (tokens), like:
    - Commands (`ls`, `echo`)
    - Arguments (`-l`, `file.txt`)
    - Operators (`|`, `>`, `>>`, `<`, `&&`, `||`, `;`)
- Tokenization is more complex than just splitting on spaces because you must respect:
    - Quoting (`"hello world"` should stay one token).
    - Escaping (`\`).
    - Environment variables (`$HOME`).
    - Subshells (`(...)`).
