/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:07:10 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/02 15:54:44 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Skips over the filename after a redirection operator, handling quotes if 
present*/
static int	skip_redirect_filename(char *input, int start)
{
	int		i;

	i = start;
	while (input[i] && !ft_isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else
			i++;
	}
	return (i);
}

/* Checks if a redirection is followed by a valid filename (not empty, not another operator) */
static char *handle_redirect_char(char *input, int *i)
{
	char *token = NULL;
	if (input[*i] == '<' && input[*i + 1] == '<')
		token = ft_strdup("<<");
	else if (input[*i] == '>' && input[*i + 1] == '>')
		token = ft_strdup(">>");
	else if (input[*i] == '<')
		token = ft_strdup("<");
	else if (input[*i] == '>')
		token = ft_strdup(">");

	if (input[*i] == input[*i + 1])
		*i += 2;
	else
		*i += 1;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i])
	{
		free(token);
		return ft_strdup("newline");
	}
	if (input[*i] == '|')
	{
		free(token);
		return ft_strdup("|");
	}
	if (input[*i] == '<')
	{
		free(token);
		if (input[*i + 1] == '<')
			return ft_strdup("<<");
		else
			return ft_strdup("<");
	}
	if (input[*i] == '>')
	{
		free(token);
		if (input[*i + 1] == '>')
			return ft_strdup(">>");
		else
			return ft_strdup(">");
	}
	free(token);
	*i = skip_redirect_filename(input, *i);
	return NULL;
}

/* Validates the overall redirection syntax in the input line, returns token fautif ou NULL */
char *validate_redirect_syntax(char *input)
{
	int i = 0;
	char *unexpected = NULL;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			unexpected = handle_redirect_char(input, &i);
			if (unexpected)
				return unexpected;
		}
		else
		{
			if (input[i] == '\'' || input[i] == '"')
				i = skip_quotes(input, i, input[i]);
			else
				i++;
		}
	}
	return NULL;
}
