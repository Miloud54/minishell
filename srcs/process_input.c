/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:04:51 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 15:05:36 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_prechecks(t_data *data, char *input)
{
	if (!input || !*input)
		return (0);
	if (!validate_syntax(input))
		return (0);
	if (ft_strcmp(input, "$?") == 0)
	{
		printf("%d\n", data->exit_status);
		return (0);
	}
	return (1);
}

static int	is_exit_cmd(t_cmd **cmds, int cmd_count)
{
	return (cmds && cmd_count == 1 && cmds[0] && cmds[0]->args
		&& cmds[0]->args[0] && ft_strcmp(cmds[0]->args[0], "exit") == 0);
}

static int	init_cmds(char *input, t_token **tokens, t_cmd ***cmds,
		int *cmd_count)
{
	*tokens = lexer(input);
	if (!*tokens)
		return (0);
	*cmds = parser(*tokens, cmd_count);
	if (!*cmds)
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	return (1);
}

static void	handle_exit_cmd(t_data *data, t_cmd **cmds, int cmd_count,
		t_token *tokens)
{
	exec_builtin(data, cmds[0]);
	cleanup_cmds(tokens, cmds, cmd_count);
	exit(data->exit_status);
}

void	process_input(t_data *data, char *input)
{
	t_token	*tokens;
	t_cmd	**cmds;
	int		cmd_count;

	if (!input_prechecks(data, input))
		return ;
	if (!init_cmds(input, &tokens, &cmds, &cmd_count))
		return ;
	expand_regular_cmds(cmds, cmd_count, data);
	if (is_exit_cmd(cmds, cmd_count))
		return (handle_exit_cmd(data, cmds, cmd_count, tokens), (void)0);
	if (cmd_count > 0)
		execute_cmds(cmds, cmd_count, data);
	cleanup_cmds(tokens, cmds, cmd_count);
}
