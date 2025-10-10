/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:07:13 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 15:07:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd_args(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = expand_variables(cmd->args[i], data);
		if (tmp != cmd->args[i])
			free(cmd->args[i]);
		cmd->args[i] = tmp;
		tmp = remove_quotes(cmd->args[i]);
		if (tmp != cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = tmp;
		}
		i++;
	}
}

void	expand_regular_cmds(t_cmd **cmds, int cmd_count, t_data *data)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (cmds[i]->args && cmds[i]->args[0]
			&& ft_strcmp(cmds[i]->args[0], "cd") == 0)
		{
			i++;
			continue ;
		}
		expand_cmd_args(cmds[i], data);
		i++;
	}
}

void	cleanup_cmds(t_token *tokens, t_cmd **cmds, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
	free_tokens(tokens);
}
