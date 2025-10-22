/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:07:10 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/10 15:16:51 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Skip filename after a redirection token. */
static int	skip_redirect_filename(char *input, int start)
{
	int	i;

	i = start;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else
			i++;
	}
	return (i);
}

static int	redirect_length(char *input, int index)
{
	if (input[index] == '<' && input[index + 1] == '<')
		return (2);
	if (input[index] == '<' && input[index + 1] == '>')
		return (2);
	if (input[index] == '>' && input[index + 1] == '>')
		return (2);
	return (1);
}

static char	*dup_redirect_token(char *input, int index)
{
	if (input[index] == '<' && input[index + 1] == '<')
		return (ft_strdup("<<"));
	if (input[index] == '<' && input[index + 1] == '>')
		return (ft_strdup("<>"));
	if (input[index] == '<')
		return (ft_strdup("<"));
	if (input[index] == '>' && input[index + 1] == '>')
		return (ft_strdup(">>"));
	return (ft_strdup(">"));
}

static char	*handle_redirect_char(char *input, int *i)
{
	int		step;

	step = redirect_length(input, *i);
	*i += step;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i])
		return (ft_strdup("newline"));
	if (input[*i] == '|')
		return (ft_strdup("|"));
	if (input[*i] == '<' || input[*i] == '>')
		return (dup_redirect_token(input, *i));
	*i = skip_redirect_filename(input, *i);
	return (NULL);
}

char	*validate_redirect_syntax(char *input)
{
	int		i;
	char	*unexpected;

	i = 0;
	unexpected = NULL;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			unexpected = handle_redirect_char(input, &i);
			if (unexpected)
				return (unexpected);
		}
		else
		{
			if (input[i] == '\'' || input[i] == '"')
				i = skip_quotes(input, i, input[i]);
			else
				i++;
		}
	}
	return (NULL);
}
