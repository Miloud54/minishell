/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:50:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 15:43:42 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts the number of commands in the token list by counting
the number of pipes (|) and adding one*/

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

/*Counts the number of argument tokens (words) in a command,
skipping over redirection tokens and their associated file tokens*/

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

/*Counts the number of redirection tokens (input, output, append,
	heredoc) in a command*/

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

/*Returns a pointer to the next pipe token in the list,
or NULL if there is none*/

t_token	*find_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	return (tokens);
}

/*These functions are used to analyze the token list and determine how many
commands, arguments, and redirections are present for parsing and memory
allocation*/