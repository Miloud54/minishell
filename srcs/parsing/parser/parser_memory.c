/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:35:00 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 16:29:31 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes a command structure with safe defaults */
void	init_cmd_defaults(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->redirect_count = 0;
}

/* Safely allocates memory for command arguments */
int	allocate_cmd_args(t_cmd *cmd, int arg_count)
{
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (0);
	return (1);
}

/* Safely allocates memory for command redirections */
int	allocate_cmd_redirects(t_cmd *cmd, int redir_count)
{
	if (redir_count > 0)
	{
		cmd->redirects = malloc(sizeof(t_redirect) * redir_count);
		if (!cmd->redirects)
			return (0);
	}
	else
		cmd->redirects = NULL;
	cmd->redirect_count = redir_count;
	return (1);
}

/* Safely allocates memory for command arguments and redirections */
int	allocate_cmd_memory(t_cmd *cmd, int arg_count, int redir_count)
{
	if (!allocate_cmd_args(cmd, arg_count))
		return (0);
	if (!allocate_cmd_redirects(cmd, redir_count))
	{
		free(cmd->args);
		cmd->args = NULL;
		return (0);
	}
	return (1);
}
