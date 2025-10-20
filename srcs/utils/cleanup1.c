/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:50:55 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/20 16:12:43 by emiliedidie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_history_safe(void)
{
	rl_clear_history();
}

void	cleanup_execution_context(t_data *data)
{
	if (!data)
		return ;
	if (!data->current_tokens && !data->current_cmds)
		return ;
	cleanup_cmds(data->current_tokens, data->current_cmds,
		data->current_cmd_count);
	data->current_tokens = NULL;
	data->current_cmds = NULL;
	data->current_cmd_count = 0;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
