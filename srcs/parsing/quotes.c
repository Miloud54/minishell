/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:39:46 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/21 20:00:22 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Finds the index of the closing quote starting from 'start' */
int	find_quote_end(char *str, int start, char quote)
{
	int		i;

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
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			if (find_quote_end(input, i, quote) == -1)
				return (1);
			i = find_quote_end(input, i, quote) + 1;
		}
		else
			i++;
	}
	return (0);
}

/* Calculates the length of the string without quotes */
static int	count_unquoted_len(char *str)
{
	int		i;
	int		len;
	char	quote;
	int		quote_end;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			quote_end = find_quote_end(str, i, quote);
			if (quote_end == -1)
				return (-1);
			len += quote_end - i - 1;
			i = quote_end + 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

/* Copies the string to 'result' without quotes */
static void	copy_without_quotes(char *str, char *result)
{
	int		i;
	int		j;
	char	quote;
	int		quote_end;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			quote_end = find_quote_end(str, i, quote);
			i++;
			while (i < quote_end)
				result[j++] = str[i++];
			i++;
		}
		else
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
	len = count_unquoted_len(str);
	if (len == -1)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(str, result);
	return (result);
}
