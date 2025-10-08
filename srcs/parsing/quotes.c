/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:39:46 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/08 12:33:18 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Finds the index of the closing quote starting from 'start' */
int	find_quote_end(char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i);
	return (-1);
}

/* Checks if the input string contains any unclosed quotes */
int	has_unclosed_quotes(char *input)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

/* Calculates the length of the string without quotes */
static int	count_unquoted_len(char *str)
{
	int	i;
	int	len;
	int	in_single;
	int	in_double;

	i = 0;
	len = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
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
	int	i;
	int	j;
	int	in_single;
	int	in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
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
