/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:07:13 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 16:19:09 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_argument(char *arg, t_data *data, t_dyn_array *builder)
{
	char	*expanded;
	char	**fields;

	expanded = expand_variables(arg, data);
	if (!expanded)
		return (0);
	fields = split_expanded_argument(expanded);
	free(expanded);
	if (!fields)
		return (0);
	if (!fields[0])
	{
		free(fields);
		return (1);
	}
	if (!append_clean_fields(fields, builder))
		return (0);
	return (1);
}

static int	assign_new_args(t_cmd *cmd)
{
	cmd->args = ft_calloc(1, sizeof(char *));
	if (!cmd->args)
		return (0);
	return (1);
}

static int	rebuild_cmd_args(t_cmd *cmd, t_data *data)
{
	t_dyn_array	builder;
	int			i;

	builder.items = NULL;
	builder.count = 0;
	builder.capacity = 0;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!process_argument(cmd->args[i], data, &builder))
		{
			ft_free_split(&builder.items);
			return (0);
		}
		i++;
	}
	ft_free_split(&cmd->args);
	if (!builder.items)
		return (assign_new_args(cmd));
	cmd->args = builder.items;
	return (1);
}

int	expand_regular_cmds(t_cmd **cmds, int cmd_count, t_data *data)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (!rebuild_cmd_args(cmds[i], data))
		{
			data->exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
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
