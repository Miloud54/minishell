/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:38 by edidier           #+#    #+#             */
/*   Updated: 2025/09/19 16:13:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/inc/libft.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

#define TOKEN_REDIR_IN 1      // "<"
#define TOKEN_HEREDOC 2       // "<<"
#define TOKEN_REDIR_OUT 3     // ">"
#define TOKEN_APPEND 4        // ">>"
#define TOKEN_PIPE 5          // "|"
#define TOKEN_CMD 6           // Commande
#define TOKEN_WORD 7


typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append; // 1 si >>, 0 si >
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;


typedef struct s_minishell
{
	char	**env;
	t_token	*tokens;
	t_cmd	*commands;
	int		last_status;
}	t_minishell;

#endif