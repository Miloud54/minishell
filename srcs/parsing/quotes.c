/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:39:46 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/10 18:18:59 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Finds the index of the closing quote starting from 'start' */
int	find_quote_end(char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (quote == '"' && str[i] == '\\' && str[i + 1] && ft_strchr("\"$\\`",
				str[i + 1]))
		{
			i += 2;
			continue ;
		}
		if (quote == '"' && str[i] == '\\' && str[i + 1] == '\n')
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

/* Checks if the input string contains any unclosed quotes */
int	has_unclosed_quotes(char *input)
{
	int				i;
	t_quote_state	state;

	i = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (input[i])
	{
		if (input[i] == '\\' && !state.in_single)
		{
			if (state.in_double && input[i + 1] && ft_strchr("\"$\\`", 
				input[i + 1]))
				i += 2;
			else if (state.in_double && input[i + 1] == '\n')
				i += 2;
			else if (!state.in_double && input[i + 1])
				i += 2;
			else
				i++;
		}
		else if (input[i] == '\'' && !state.in_double)
		{
			state.in_single = !state.in_single;
			i++;
		}
		else if (input[i] == '"' && !state.in_single)
		{
			state.in_double = !state.in_double;
			i++;
		}
		else
			i++;
	}
	return (state.in_single || state.in_double);
}

/* Calculates the length of the string without quotes */
static int	count_unquoted_len(char *str)
{
	int				i;
	int				len;
	t_quote_state	state;

	i = 0;
	len = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (str[i])
	{
		if (str[i] == '\\' && !state.in_single)
		{
			if (state.in_double && str[i + 1] && ft_strchr("\"$\\`", str[i
					+ 1]))
			{
				len++;
				i += 2;
				continue ;
			}
			if (state.in_double && str[i + 1] == '\n')
			{
				i += 2;
				continue ;
			}
			if (!state.in_double && str[i + 1])
			{
				len++;
				i += 2;
				continue ;
			}
		}
		if (str[i] == '\'' && !state.in_double)
		{
			state.in_single = !state.in_single;
			i++;
			continue ;
		}
		if (str[i] == '"' && !state.in_single)
		{
			state.in_double = !state.in_double;
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

/* Copies the string to 'result' without quotes */
static void	copy_without_quotes(char *str, char *result)
{
	int				i;
	int				j;
	t_quote_state	state;

	i = 0;
	j = 0;
	state.in_single = 0;
	state.in_double = 0;
	while (str[i])
	{
		if (str[i] == '\\' && !state.in_single)
		{
			if (state.in_double && str[i + 1] && ft_strchr("\"$\\`", str[i
					+ 1]))
			{
				result[j++] = str[i + 1];
				i += 2;
				continue ;
			}
			if (state.in_double && str[i + 1] == '\n')
			{
				i += 2;
				continue ;
			}
			if (!state.in_double && str[i + 1])
			{
				result[j++] = str[i + 1];
				i += 2;
				continue ;
			}
		}
		if (str[i] == '\'' && !state.in_double)
		{
			state.in_single = !state.in_single;
			i++;
			continue ;
		}
		if (str[i] == '"' && !state.in_single)
		{
			state.in_double = !state.in_double;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
}

/* Returns a new string with all quotes removed */
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
