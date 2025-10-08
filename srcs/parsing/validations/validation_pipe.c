/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:07:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/08 12:36:30 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Returns a malloc'd unexpected token string if pipe syntax is invalid,
   otherwise NULL. This function skips quoted regions. */
char	*validate_pipe_syntax(char *input)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quotes(input, i, input[i]);
		else if (input[i] == '|')
		{
			/* Check for content before the pipe */
			k = i - 1;
			while (k >= 0 && ft_isspace(input[k]))
			{
				if (input[k] == '\n')
					return (ft_strdup("|"));
				k--;
			}
			if (k < 0)
				return (ft_strdup("|"));
			/* Find next non-space token */
			j = i + 1;
			while (input[j] && ft_isspace(input[j]))
				j++;
			if (!input[j])
				return (ft_strdup("newline"));
			if (input[j] == '|')
			{
				/* Collect consecutive '|' characters starting at j */
				k = j;
				while (input[k] == '|')
					k++;
				return (ft_substr(input, j, k - j));
			}
			/* Otherwise there is content after the pipe: continue */
			i++;
		}
		else
			i++;
	}
	return (NULL);
}
