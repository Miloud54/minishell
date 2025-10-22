/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:52:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 13:50:40 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Determines the type of redirection operator and advances the index */
t_token_type	get_redirect_type(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			return (TOKEN_REDIR_HEREDOC);
		}
		(*i)++;
		return (TOKEN_REDIR_IN);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*i += 2;
			return (TOKEN_REDIR_APPEND);
		}
		(*i)++;
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

/* Creates a pipe token and advances the index */
t_token	*handle_pipe_token(int *i)
{
	*i += 1;
	return (create_token(ft_strdup("|"), TOKEN_PIPE));
}

/* Creates a redirection token and advances the index */
t_token	*handle_redirect_token(char *input, int *i)
{
	char	*value;

	if (input[*i] == input[*i + 1])
		value = ft_substr(input, *i, 2);
	else
		value = ft_substr(input, *i, 1);
	return (create_token(value, get_redirect_type(input, i)));
}

/* Creates a word token from the input */
t_token	*handle_word_token(char *input, int *i)
{
	char	*value;

	value = extract_word(input, i);
	return (create_token(value, TOKEN_WORD));
}
