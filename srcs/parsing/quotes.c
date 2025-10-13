/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:39:46 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/13 17:40:21 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	skip_escape(char *input, int *i, t_quote_state *state)
{
	if (input[*i] != '\\' || state->in_single)
		return (0);
	if (state->in_double && input[*i + 1] == '\n')
	{
		*i += 2;
		return (1);
	}
	if (state->in_double && input[*i + 1] && ft_strchr("\"$\\`", input[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	if (!state->in_double && input[*i + 1])
	{
		*i += 2;
		return (1);
	}
	(*i)++;
	return (1);
}

static int	toggle_quote_state(char c, t_quote_state *state)
{
	if (c == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		return (1);
	}
	if (c == '"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		return (1);
	}
	return (0);
}

int	find_quote_end(char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (quote == '"' && str[i] == '\\' && str[i + 1] == '\n')
		{
			i += 2;
			continue ;
		}
		if (quote == '"' && str[i] == '\\' && str[i + 1] && ft_strchr("\"$\\`",
				str[i + 1]))
		{
			i += 2;
			continue ;
		}
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	has_unclosed_quotes(char *input)
{
	int				i;
	t_quote_state	state;

	if (!input)
		return (0);
	state.in_single = 0;
	state.in_double = 0;
	i = 0;
	while (input[i])
	{
		if (skip_escape(input, &i, &state))
			continue ;
		if (toggle_quote_state(input[i], &state))
		{
			i++;
			continue ;
		}
		i++;
	}
	return (state.in_single || state.in_double);
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	if (has_unclosed_quotes(str))
		return (NULL);
	len = count_unquoted_len(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(str, result);
	return (result);
}
