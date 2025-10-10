/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:07:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/10 15:21:14 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	skip_spaces_and_newline_left(char *input, int i)
{
	int	k;

	k = i - 1;
	while (k >= 0 && ft_isspace(input[k]))
	{
		if (input[k] == '\n')
			return (-1);
		k--;
	}
	return (k);
}

static int	skip_spaces_right(char *input, int i)
{
	int	j;

	j = i + 1;
	while (input[j] && ft_isspace(input[j]))
		j++;
	return (j);
}

static char	*check_pipe_error(char *input, int i)
{
	int		k;
	int		j;

	k = skip_spaces_and_newline_left(input, i);
	if (k < 0)
		return (ft_strdup("|"));
	j = skip_spaces_right(input, i);
	if (!input[j])
		return (ft_strdup("newline"));
	if (input[j] == '|')
	{
		k = j;
		while (input[k] == '|')
			k++;
		return (ft_substr(input, j, k - j));
	}
	return (NULL);
}

/* Returns a malloc'd unexpected token string if pipe syntax is invalid,
   otherwise NULL. This function skips quoted regions. */
char	*validate_pipe_syntax(char *input)
{
	int		i;
	char	*err;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else if (input[i] == '|')
		{
			err = check_pipe_error(input, i);
			if (err)
				return (err);
			i++;
		}
		else
			i++;
	}
	return (NULL);
}
