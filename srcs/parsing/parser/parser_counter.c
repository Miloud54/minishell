/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:50:00 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 16:35:52 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

int	count_args_in_cmd(t_token *start, t_token *end)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			current = current->next;
			if (current && current != end)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	return (count);
}

int	count_redirect_in_cmd(t_token *start, t_token *end)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
			count++;
		current = current->next;
	}
	return (count);
}

t_token	*find_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	return (tokens);
}
