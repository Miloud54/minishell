/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:04:51 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 15:43:29 by edidier          ###   ########.fr       */
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

static int	is_exit_cmd(t_cmd **cmds, int cmd_count)
{
	return (cmds && cmd_count == 1 && cmds[0] && cmds[0]->args
		&& cmds[0]->args[0] && ft_strcmp(cmds[0]->args[0], "exit") == 0);
}

static void	free_all_cmds(t_cmd **cmds, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}

static void	handle_exit_cmd(t_data *data, t_cmd **cmds, int cmd_count,
		t_token *tokens)
{
	exec_builtin(data, cmds[0]);
	free_all_cmds(cmds, cmd_count);
	free_tokens(tokens);
	exit(data->exit_status);
}

static void	process_input(t_data *data, char *input)
{
	t_token	*tokens;
	t_cmd	**cmds;
	int		cmd_count;
	int		i;

	if (!input || !*input)
		return ;
	if (ft_strcmp(input, "$?") == 0)
		return ((void)printf("%d\n", data->exit_status));
	tokens = lexer(input);
	if (!tokens)
		return ;
	cmds = parser(tokens, &cmd_count);
	if (!cmds)
		return (free_tokens(tokens), (void)0);
	i = -1;
	while (++i < cmd_count)
		expand_cmd_args(cmds[i], data);
	if (is_exit_cmd(cmds, cmd_count))
		return (handle_exit_cmd(data, cmds, cmd_count, tokens), (void)0);
	if (cmd_count > 0)
		execute_commands(cmds, cmd_count, data);
	free_all_cmds(cmds, cmd_count);
	free_tokens(tokens);
}
