/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:38 by edidier           #+#    #+#             */
/*   Updated: 2025/10/08 12:24:31 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/* Readline function declarations à retirer car juste pour Mac */
extern void				rl_replace_line(const char *text, int clear_undo);
extern void				rl_redisplay(void);

// #define TOKEN_REDIR_IN 1      // "<"
// #define TOKEN_HEREDOC 2       // "<<"
// #define TOKEN_REDIR_OUT 3     // ">"
// #define TOKEN_APPEND 4        // ">>"
// #define TOKEN_PIPE 5          // "|"
// #define TOKEN_CMD 6           // Command
// #define TOKEN_WORD 7			// Word

/* ************************************************************************** */

/*Ajout bru 21/09/25: */

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define MAX_PATH 4096
# define PROMPT "\033[0;32mminishell$ \033[0m"

/* ************************************************************************** */
/*                              GLOBAL VARIABLES                              */
/* ************************************************************************** */

extern int				g_signal_status;

/* ************************************************************************** */
/*                                ENUMS                                       */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}						t_token_type;

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	t_token_type		type;
	char				*file;
	int					heredoc_fd;
}						t_redirect;

typedef struct s_cmd
{
	char				**args;
	char				**cmd_path;
	t_redirect			*redirects;
	int					redirect_count;
}						t_cmd;

typedef struct s_data
{
	char				**envp;
	int					exit_status;
	char				*pwd;
	char				*oldpwd;
	int					stdin_backup;
	int					stdout_backup;
}						t_data;

typedef struct s_parse_result
{
	unsigned long long	result;
	int					overflow;
}						t_parse_result;

typedef struct s_copy_context
{
	char				*input;
	t_data				*data;
	char				*result;
	int					*i;
	int					*j;
}						t_copy_context;

typedef struct s_size_context
{
	char				*input;
	t_data				*data;
	int					*i;
	int					*size;
	int					*in_single_quotes;
}						t_size_context;

typedef struct s_pipe_data
{
	int					cmd_index;
	int					*pipe_fd;
	int					prev_pipe;
	int					cmd_count;
}						t_pipe_data;

typedef struct s_child_args
{
	t_cmd				**cmds;
	int					i;
	int					cmd_count;
	t_pipe_data			*pipe_data;
	int					*pipe_fd;
	int					prev_pipe;
	t_data				*data;
}						t_child_args;

typedef struct s_iter_args
{
	t_cmd				**cmds;
	int					i;
	int					cmd_count;
	int					*prev_pipe;
	t_data				*data;
}						t_iter_args;

/* process_input.c: */
void					process_input(t_data *data, char *input);

/* builtins/builtins.c: */
int						is_exit_command(const char *input);
bool					is_builtin(char *cmd);
void					exec_builtin(t_data *data, t_cmd *cmd);

/* builtins/everything.c: */
int						ft_cd(t_data *data, char **argv);
void					ft_env(t_data *data, t_cmd *cmd);
void					ft_echo(t_cmd *cmd, t_data *data);
int						ft_exit(t_data *data, char **argv);
void					ft_unset(t_cmd *cmd, t_data *data);
int						ft_pwd(char **argv);
void					ft_export(t_cmd *cmd, t_data *data);

/* builtins/cd_utils.c */
int						update_env_var(char ***envp, char *name, char *value);
char					*expand_env_var(const char *arg, char **envp);

/* builtins/export_utils.c: */
void					add_or_update_env(t_data *data, const char *arg);
void					add_env_var(t_data *data, const char *arg);
int						replace_env_var(t_data *data, const char *arg, int len);
void					sort_env(char **envp);

/* builtins/exit_utils.c: */
int						parse_sign(const char *str, int *i);
int						parse_digits(const char *str, int *i, int sign,
							t_parse_result *res);
void					skip_spaces(const char *str, int *i);

/* parsing/validation.c: */
int						validate_syntax(char *input);

/* parsing/validation_pipe.c */
char			*validate_pipe_syntax(char *input);

/* parsing/quotes.c: */
int			find_quote_end(char *str, int start, char quote);
char			*remove_quotes(char *str);
int			has_unclosed_quotes(char *input);

/* parsing/tokens.c: */
t_token					*create_token(char *value, t_token_type type);
void					add_token(t_token **tokens, t_token *new_token);

/* parsing/tokens_utils.c */
char					**tokens_to_argv(t_token *tokens);

/* parsing/validation_redirection.c: */
char					*validate_redirect_syntax(char *input);

/* utils/cleanup1.c: */
void					free_data(t_data *data);
void					free_tokens(t_token *tokens);
void					free_argv(char **argv);

/* utils/cleanup2.c: */
void					free_cmd(t_cmd *cmd);
char					*ft_strjoin_free(char *s1, char *s2);

/* utils/exits.c: */
void					error_exit(char *msg, int exit_code);
void					perror_exit(char *msg, int exit_code);

/* utils/init_data.c: */
void					init_data(t_data *data, char **envp);
char					*get_env_var(char **envp, char *name);

/* utils/init_signals.c: */
void					init_signals(void);

/* parsing/expansion/expansion.c: */
char					*expand_variables(char *input, t_data *data);

/* parsing/expansion/expansion_vars.c: */
char					*get_var_name(char *input, int *i);
char					*get_var_value(char *var_name, t_data *data);
int						should_expand_int_quotes(char *input, int i,
							int in_single_quotes);
void					copy_variable_value(char *var_value, char *result,
							int *j);

/* parsing/expansion_size.c: */
int						calculate_expanded_size(char *input, t_data *data);

/* parsing/expansion/expansion_size.c: */
int						handle_quotes(char c, int *in_single_quotes, int *size,
							int *i);
void					handle_variable_expansion(char *input, t_data *data,
							int *i, int *size);
int						calculate_expanded_size(char *input, t_data *data);

/* parsing/expansion/expansion_process.c: */
char					*perform_expansion(char *input, t_data *data,
							int expanded_size);

/* parsing/lexer/lexer.c: */
int						is_special_char(char c);
int						skip_quotes(char *input, int i, char quote);
char					*extract_word(char *input, int *i);
t_token					*lexer(char *input);

/* parsing/lexer/lexer_utils.c*/
t_token_type			get_redirect_type(char *input, int *i);
t_token					*handle_pipe_token(int *i);
t_token					*handle_redirect_token(char *input, int *i);
t_token					*handle_word_token(char *input, int *i);

/* parsing/parser.c */
t_cmd					**parser(t_token *tokens, int *cmd_count);

/* parsing/parser_validation.c */
int						validate_token_sequence(t_token *tokens);

/* parsing/parser_counter.c */
int						count_commands(t_token *tokens);
int						count_args_in_cmd(t_token *start, t_token *end);
int						count_redirect_in_cmd(t_token *start, t_token *end);
t_token					*find_next_pipe(t_token *tokens);

/* parsing/parser_memory.c */
void					init_cmd_defaults(t_cmd *cmd);
int						allocate_cmd_args(t_cmd *cmd, int arg_count);
int						allocate_cmd_redirects(t_cmd *cmd, int redir_count);
int						allocate_cmd_memory(t_cmd *cmd, int arg_count,
							int redir_count);

/* parsing/parser_processing.c */
int						parse_redirects(t_cmd *cmd, t_token *start,
							t_token *end);
t_cmd					*parse_single_cmd(t_token *start, t_token *end);

/* parsing/parser_args.c */
int						parse_args(t_cmd *cmd, t_token *start, t_token *end);
t_cmd					*create_new_cmd(void);
int						fill_cmd_content(t_cmd *cmd, t_token *start,
							t_token *end);
void					cleanup_commands_on_error(t_cmd **commands, int count);

/* exec/exec.c */
char					*find_executable(char *cmd, char **envp);
int						execute_single_command(t_cmd *cmd, t_data *data);

/* exec/exec_utils.c: */
char					*search_path_in_env(char *cmd, char **envp);
int						run_external_command(char *cmd_path, t_cmd *cmd,
							t_data *data);
int						is_delimiter(char *line, char *delimiter);
void					write_heredoc_line(int fd, char *line, t_data *data);
void					read_heredoc_input(int write_fd, char *delimiter,
							t_data *data);

/* exec/executor.c */
int						execute_commands(t_cmd **commands, int cmd_count,
							t_data *data);

/* exec/pipes/everything */
int						execute_pipeline(t_cmd **commands, int cmd_count,
							t_data *data);
int						create_pipe_if_needed(int i, int cmd_count,
							int pipe_fd[2]);
int						handle_parent_process(int pipe_fd[2], int prev_pipe,
							int is_last_cmd);
int						wait_all_pipeline_children(int cmd_count);
void					execute_piped_command(t_cmd *cmd, t_pipe_data *data,
							t_data *shell_data);
int						setup_pipeline_heredocs(t_cmd **commands, int cmd_count,
							t_data *data);

/* exec/redir.c */
int						setup_redirections(t_cmd *cmd, t_data *data);
void					restore_std_fds(t_data *data);
int						backup_std_fds(t_data *data);

/* exec/redir_utils.c: */
int						handle_in_redir(t_redirect *redir, t_data *data);
int						handle_out_redir(t_redirect *redir, t_data *data);
int						handle_heredoc_redir(t_redirect *redir, t_data *data);

/* exec/heredoc.c */
int						setup_heredoc(t_redirect *redirect, t_data *data);
int						handle_heredoc_redirect(t_redirect *redirect,
							t_data *data);

/* exec/heredoc_utils.c: */
int						is_delimiter(char *line, char *delimiter);
void					write_heredoc_line(int fd, char *line, t_data *data);
void					read_heredoc_input(int write_fd, char *delimiter,
							t_data *data);

/* parsing/parse_heredoc.c */
int						setup_heredoc_at_parse(t_redirect *redirect,
							t_data *data);
int						write_heredoc_to_file(int fd, char *delimiter,
							t_data *data);

/* ************************************************************************** */

#endif
