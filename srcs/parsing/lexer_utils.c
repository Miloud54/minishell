/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:52:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/22 15:03:28 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_token	*handle_pipe_token(int *i)
{
	*i += 1;
	return (create_token(ft_strdup("|"), TOKEN_PIPE));
}

t_token	*handle_redirect_token(char *input, int *i)
{
	char	*value;

	if (input[*i] == input[*i + 1])
		value = ft_substr(input, *i, 2);
	else
		value = ft_substr(input, *i, 1);
	return (create_token(value, get_redirect_type(input, i)));
}

t_token	*handle_word_token(char *input, int *i)
{
	char	*value;

	value = extract_word(input, i);
	return (create_token(value, TOKEN_WORD));
}
