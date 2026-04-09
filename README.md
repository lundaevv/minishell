# Unix Shell Implementation

A custom Unix shell written in C, implementing core Bash features such as process execution, pipes, redirections, and environment variable handling.

## Overview

This project is a custom Unix shell that replicates core behavior of Bash, focusing on process control, inter-process communication, and low-level I/O.
It supports command execution, environment variables, pipes, redirections, and built-in commands, while focusing on low-level Unix system programming concepts such as processes, file descriptors, and signal handling.

## Features

- Interactive shell prompt
- Command parsing and tokenization
- Execution of external programs using fork and execve
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variable expansion
- Pipes (`|`)
- Input and output redirections (`<`, `>`, `>>`)
- Signal handling (`Ctrl+C`, `Ctrl+\`, `Ctrl+D`)
- Exit status handling (`$?`)

## Tech Stack

- C
- Unix system calls (`fork`, `execve`, `pipe`, `dup2`)
- GNU Readline

## Core Concepts

- Process creation and management
- File descriptors and redirections
- Inter-process communication with pipes
- Parsing and tokenization
- Environment management
- Signal handling

## Architecture

The shell is organized into several main stages:

1. **Input handling**
   - Reads user input and displays the prompt
2. **Lexer / Tokenizer**
   - Splits input into meaningful tokens while handling quotes and operators
3. **Parser**
   - Builds structured command representations from tokens
4. **Executor**
   - Handles process creation, pipes, and execution flow
5. **Pipes and redirections**
   - Configures file descriptors for command chaining and input/output redirection
  
## Challenges

- Implementing a robust parser with support for quotes and environment variables
- Managing file descriptors across multiple processes
- Handling signals consistently with Bash behavior
- Avoiding memory leaks in a long-running process
- Implementing correct process synchronization and exit status handling

## ⚙️ Build and Run

```bash
make
./minishell
```
Launches the interactive shell.

## Example

```bash
$ ls -l | grep .c > output.txt
```
This command lists files, filters `.c` files, and writes the result to a file.

## Requirements

- GCC or Clang compiler
- GNU Readline library
- Unix-like environment (macOS, Linux)

## Project Structure

```bash
minishell/
├── src/        # Source files
├── includes/   # Header files
├── libft/      # Utility library
├── Makefile
└── README.md
```

## Authors

- **Vitali Lund**  
  GitHub: https://github.com/lundaevv
- **GuljaWinchester**  
  GitHub: https://github.com/GuljaWinchester
