/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:10:38 by edidier           #+#    #+#             */
/*   Updated: 2025/09/19 15:56:28 by bde-la-p         ###   ########.fr       */
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

typedef struct	s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{
	char			**args;
	int				input_fd;
	int				output_fd;
	struct	s_cmd	*next;
}	t_cmd;


typedef struct s_ms
{
	int	last_status;
}		t_ms;

#endif