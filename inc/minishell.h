/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:38 by edidier           #+#    #+#             */
/*   Updated: 2025/09/24 17:56:03 by edidier          ###   ########.fr       */
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
# define PROMPT "minishell$ "

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

/* builtins/builtins.c: */
int						is_exit_command(const char *input);

/* builtins/*.c: */
int						ft_cd(t_data *data, char **argv);
void					ft_env(t_data *data, t_cmd *cmd);
void					ft_echo(t_cmd *cmd, t_data *data);
int						ft_exit(t_data *data, char **argv);

/* builtins/cd_utils.c */
int						update_env_char(char ***envp, char *name, char *value);

/* builtins/exit_utils.c */
int						parse_sign(const char *str, int *i);
int						parse_digits(const char *str, int *i, int sign,
							t_parse_result *res);
void					skip_spaces(const char *str, int *i);

/* parsing/validation.c: */
int						validate_syntax(char *input);

/* parsing/validation_pipe.c */
int						validate_pipe_syntax(char *input);

/* parsing/quotes.c: */
int						find_quote_end(char *str, int start, char quote);
char					*remove_quotes(char *str);
int						has_unclosed_quotes(char *input);

/* parsing/tokens.c: */
t_token					*create_token(char *value, t_token_type type);
void					add_token(t_token **tokens, t_token *new_token);

/* parsing/tokens_utils.c */
char					**tokens_to_argv(t_token *tokens);

/* parsing/validation_redirection.c: */
int						validate_redirect_syntax(char *input);

/* utils/cleanup1.c: */
void					free_data(t_data *data);
void					free_tokens(t_token *tokens);
void					free_argv(char **argv);

/* utils/cleanup2.c: */
void					free_cmd(t_cmd *cmd);

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

/* ************************************************************************** */

/*before 21/09 : */

// typedef struct s_token
// {
// 	char			*value;
// 	int				type;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// }					t_token;

// typedef struct s_cmd
// {
// 	char			**args;
// 	char			*input_file;
// 	char			*output_file;
// 	int				append; // 1 si >>, 0 si >
// 	struct s_cmd	*prev;
// 	struct s_cmd	*next;
// }					t_cmd;

// typedef struct s_minishell
// {
// 	char	**env;
// 	t_token	*tokens;
// 	t_cmd	*commands;
// 	int		last_status;
// }			t_minishell;

// /*Utils*/
// void		free_array(char **array);

// /*Tokenization*/
// void		free_tokens(t_token **head);
// t_token		*tokenize(char *line);
// int			append_token(t_token **head, char *value, int type);
// bool		is_operator(char *word);
// // int			get_token_type(char *word);

// /*Debug*/
// void		print_tokens(t_token *head);

#endif