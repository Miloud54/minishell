/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:07:10 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/22 15:11:24 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	skip_redirect_filename(char *input, int start)
{
	int		i;

	i = start;
	while (input[i] && ft_isspace(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else
			i++;
	}
	return (i);
}

static int	handle_redirect_char(char *input, int *i)
{
	if (input[*i] == input[*i + 1])
		*i += 2;
	else
		*i += 1;
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (!input[*i] || input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (0);
	*i = skip_redirect_filename(input, *i);
	return (1);
}

int	validate_redirect_syntax(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (!handle_redirect_char(input, &i))
				return (0);
		}
		else
		{
			if (input[i] == '\'' || input[i] == '"')
				i = skip_quotes(input, i, input[i]);
			else
				i++;
		}
	}
	return (1);
}
