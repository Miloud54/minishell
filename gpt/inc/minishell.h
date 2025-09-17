#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>

# include <readline/history.h>
# include <ctype.h>
# include <signal.h>


extern volatile sig_atomic_t g_last_signal;

char *readline(const char *prompt);
void add_history(const char *line);
int rl_on_new_line(void);
void rl_replace_line(const char *text, int clear_undo);
void rl_redisplay(void);
void rl_clear_history(void);

char **tokenize(const char *line);
void free_tokens(char **tokens);

int is_builtin(char **argv);
int run_builtin(char **argv);

int find_and_exec(char **argv, char **envp);

int execute_pipeline(char **tokens, char **envp);

#endif
