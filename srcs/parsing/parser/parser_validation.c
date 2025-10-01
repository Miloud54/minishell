/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:35:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:50:53 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if pipe token is valid in sequence
(not at the end and not followed by another pipe)*/

static int	is_pipe_valid(t_token *current)
{
	if (!current->next || current->next->type == TOKEN_PIPE)
		return (0);
	return (1);
}

/*Checks if redirection token is valid in sequence
(must be followed by a word token == a filename)*/

static int	is_redirect_valid(t_token *current)
{
	if (!current->next || current->next->type != TOKEN_WORD)
		return (0);
	return (1);
}

/*Validates if a token sequence is valid for parsing
(no invalid pipes or redirections)*/

int	validate_token_sequence(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!is_pipe_valid(current))
				return (0);
		}
		if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			if (!is_redirect_valid(current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

/*These functions are used to validate the syntax
of the token list before parsing it into commands*/