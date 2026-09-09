# minishell

A simplified Unix shell written in C, reimplementing core bash-like behavior: command parsing, pipes, redirections, environment variable expansion, signal handling and built-in commands. This is a project from the 42 core curriculum.

## 📋 Description

**minishell** reads a command line, tokenizes and parses it into a pipeline of commands, expands environment variables and quotes, then executes the pipeline while handling redirections (`<`, `>`, `>>`), heredocs (`<<`), and built-in commands. It relies on the `readline` library for interactive input and history.

## 🛠️ Build

```bash
make          # builds libft and the minishell executable
make clean    # cleans libft and object files
make fclean   # clean + removes the executable
make re       # fclean + make
```

**Dependency:** the GNU `readline` library must be installed (`-lreadline`).

## 🚀 Usage

```bash
./minishell
```

```bash
minishell$ echo hello | grep h > output.txt
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
minishell$ cd ..
minishell$ exit
```

## ⚙️ Built-in commands

| Builtin | Description |
|---|---|
| `cd` | Changes the current directory (supports `CDPATH`, `HOME`, `OLDPWD`) |
| `echo` | Prints arguments (supports `-n`) |
| `env` | Displays environment variables |
| `exit` | Exits the shell with an optional status code |
| `export` | Sets or updates an environment variable |
| `pwd` | Prints the current working directory |
| `unset` | Removes an environment variable |

## ✨ Features

- Command pipelines (`cmd1 | cmd2 | ... | cmdn`)
- Redirections: input (`<`), output (`>`), append (`>>`), heredoc (`<<`)
- Single and double quote handling, including expansion inside double quotes
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) matching bash behavior
- Command history via `readline`
- Syntax and quote validation with descriptive errors

## 📁 Project structure

```
minishell/
├── inc/
│   └── minishell.h              # Structs, enums, prototypes
├── libft/                        # Personal libft (includes ft_printf and get_next_line)
├── srcs/
│   ├── main.c                     # Entry point: readline loop, signal setup
│   ├── process_input.c            # Orchestrates parsing of a single input line
│   ├── process_input_utils.c       # Command expansion / cleanup helpers
│   ├── process_input_utils2.c      # IFS (word-splitting) helper
│   ├── process_input_expand_array.c # Builds expanded argument arrays
│   ├── process_input_expand_split.c # Splits expanded arguments on IFS
│   ├── parsing/
│   │   ├── lexer/                  # Tokenizes the raw input line
│   │   ├── parser/                 # Builds t_cmd structures from tokens
│   │   ├── expansion/              # $VAR and $? expansion logic
│   │   ├── validations/            # Syntax checks (pipes, redirections, sequences)
│   │   ├── quotes.c                # Quote parsing / removal
│   │   ├── quotes_state.c          # Quote/escape state machine
│   │   ├── quotes_utils.c          # Quote length/copy helpers
│   │   ├── tokens.c                # Token creation and linking
│   │   ├── tokens_utils.c          # Token list -> argv conversion
│   │   └── parse_heredoc.c         # Heredoc setup during parsing
│   ├── exec/
│   │   ├── exec.c                  # Executable lookup, single command execution
│   │   ├── exec_utils.c            # PATH search, external command running
│   │   ├── executor.c              # Dispatches single command vs pipeline execution
│   │   ├── redir.c                 # Redirection setup / std fd backup-restore
│   │   ├── redir_utils.c           # Per-redirection handlers (in/out/heredoc)
│   │   ├── heredoc.c               # Heredoc temp file creation and handling
│   │   ├── heredoc_setup.c         # Heredoc setup across a pipeline
│   │   ├── heredoc_files.c         # Heredoc temp file management
│   │   ├── heredoc_utils.c         # Delimiter checks, line writing, EOF warning
│   │   └── pipes/                  # Pipeline creation, forking, child execution, waiting
│   ├── builtins/
│   │   ├── builtins.c              # Builtin dispatch table
│   │   ├── cd/                     # cd command (path resolution, CDPATH, env updates)
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c / exit_utils.c
│   │   ├── export.c / export_utils.c
│   │   ├── pwd.c
│   │   └── unset.c
│   └── utils/
│       ├── cleanup1.c / cleanup2.c / cleanup_cmd.c / cleanup_fd.c  # Memory and fd cleanup
│       ├── exits.c                 # Error exit helpers
│       ├── globals.c               # Global signal status variable
│       ├── init_data.c             # Shell state initialization
│       └── init_signals.c          # Signal handler setup
├── Makefile
└── README.md
```

## ⚙️ How it works

1. `main` initializes shell data (`init_data`) and signal handlers (`init_signals`), then loops on `readline` to read each command line.
2. `process_input` validates syntax (`validation.c`), tokenizes the line (`lexer.c`), builds the command list (`parser.c`), and expands variables/quotes (`expansion.c`, `quotes.c`).
3. `execute_cmds` dispatches to either `execute_single_command` (builtin or external, no pipe) or `execute_pipeline` for multi-command lines.
4. For pipelines, `pipes.c` creates a pipe per stage, forks a child per command, wires stdin/stdout through the pipes, and waits for every child to finish.
5. Redirections (`<`, `>`, `>>`, `<<`) are resolved by `redir.c` / `heredoc.c` before each command runs, backing up and restoring the shell's standard file descriptors as needed.
6. Builtins (`cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`) run directly in the shell process instead of being forked, except when part of a pipeline.
7. Cleanup functions (`utils/cleanup*.c`) free tokens, commands, and file descriptors after each command line.

## ✅ Norm

The project follows the **42 Norm** (Norminette).
