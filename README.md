*This project has been created as part of the 42 curriculum by rpinheir.*

## Description

Pipex is a program that replicates the behavior of shell pipes in C. It takes an input file, applies two or more shell commands in sequence (piping the output of one to the input of the next), and writes the final result to an output file.

The mandatory part handles a single pipe between two commands:
```
./pipex infile "cmd1" "cmd2" outfile
```
Equivalent to: `< infile cmd1 | cmd2 > outfile`

The bonus part extends this with:
- **Multiple pipes**: chaining 3 or more commands
- **Here_doc**: reading input from stdin until a delimiter, with append mode (`>>`)

## Instructions

### Compilation

```bash
make        # Build mandatory version
make bonus  # Build bonus version (multi-pipe + here_doc)
make clean  # Remove object files
make fclean # Full clean (objects + binary)
make re     # Rebuild from scratch
```

### Execution

**Mandatory (2 commands):**
```bash
./pipex infile "ls -l" "wc -l" outfile
```

**Bonus - Multiple pipes:**
```bash
./pipex infile "grep foo" "sort" "wc -l" outfile
```

**Bonus - Here_doc:**
```bash
./pipex here_doc EOF "cat" "wc -l" outfile
```

## Resources

- [pipe(2) - Linux man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [dup2(2) - Linux man page](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [execve(2) - Linux man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [fork(2) - Linux man page](https://man7.org/linux/man-pages/man2/fork.2.html)

### AI usage

AI tools (Claude Code) were used to assist with debugging the pipe management logic, specifically for identifying a missing `exit()` call in command error handling and for structuring the multi-pipe bonus implementation. All code was coded and tested manually.
