# minishell

> 42 Paris project — Reimplementing a simplified shell
>
> This is a group project done by *tlecuyer* and *jferrand* (me)

## 📌 Description

minishell reimplements a subset of bash's behavior: interactive input reading, command-line parsing (quotes, environment variable expansion, redirections, pipes), execution of builtin and external commands, and signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).

## 🎯 Bonus implemented

All bonus features are implemented (`&&`/`||` logical operators with parentheses and wildcards). There is no separate `make bonus` target — everything is built directly with `make`.

## 🎯 Skills demonstrated

- Advanced parsing: tokenization, single/double quote handling, variable expansion (`$VAR`, `$?`)
- Process execution: `fork`, `execve`, multiple pipe handling, redirections (`<`, `>`, `>>`, `<<` heredoc)
- Builtin implementation (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Signal handling and exit status tracking (`$?`)
- Careful memory management on a complex data structure (command list/tree)

## 🛠️ Stack & constraints

- **Language**: C
- **Build**: Makefile
- **Dependencies**: Libft, `readline` (line editing and history)
- **Constraints**: 42 Norm, behavior aligned with bash on standard test cases, no memory leaks (aside from `readline`'s own known internal leaks)

## 🚀 Build & usage

```bash
make
./minishell
```

```bash
minishell$ echo "hello" | grep h | wc -l
minishell$ export VAR=42 && echo $VAR
```

## 📁 Structure

```
.
├── Makefile
├── sources/
│   ├── parsing/
│   ├── execution/
│   └── builtins/
└── sources_libft/
```

## 📝 Notes

The most demanding project of the common core in C: it combines parsing, process management, and signal handling into a single coherent program — with all bonus features completed.
