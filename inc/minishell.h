/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:38 by edidier           #+#    #+#             */
/*   Updated: 2025/09/21 20:16:57 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

// #define TOKEN_REDIR_IN 1      // "<"
// #define TOKEN_HEREDOC 2       // "<<"
// #define TOKEN_REDIR_OUT 3     // ">"
// #define TOKEN_APPEND 4        // ">>"
// #define TOKEN_PIPE 5          // "|"
// #define TOKEN_CMD 6           // Command
// #define TOKEN_WORD 7		  // Word

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

extern int	g_signal_status;

/* ************************************************************************** */
/*                                ENUMS                                       */
/* ************************************************************************** */

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
}	t_redirect;


typedef struct s_cmd
{
	char		**args;
	t_redirect	*redirects;
	int			redirect_count;
}	t_cmd;


typedef struct s_data
{
	char	**envp;
	int		exit_status;
	char	*pwd;
	char	*oldpwd;
	int		stdin_backup;
	int		stdout_backup;
}	t_data;

/* parsing/validation.c: */
int	validate_syntax(char *input);

/* parsing/quotes.c: */
int		find_quote_end(char *str, int start, char quote);
char	*remove_quotes(char *str);
int		has_unclosed_quotes(char *input);

/* parsing/validation_redirection.c: */
int	validate_redirect_syntax(char *input);

/* utils/exits.c: */
void	error_exit(char *msg, int exit_code);

/* utils/init_data.c: */
void	init_data(t_data *data, char **envp);

/* utils/init_signals.c: */
void	init_signals(void);

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