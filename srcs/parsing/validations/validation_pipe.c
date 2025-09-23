/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:07:28 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/22 15:11:08 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Checks if there is non-space content before the pipe position */
static int	has_content_before(char *input, int pipe_pos)
{
	int		i;

	i = pipe_pos - 1;
	while (i >= 0)
	{
		if (!ft_isspace(input[i]))
			return (1);
		i--;
	}
	return (0);
}

/* Checks if there is non-space content after the pipe position */
static int	has_content_after(char *input, int pipe_pos)
{
	int		i;

	i = pipe_pos + 1;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

/* Checks if there is content both before and after the pipe */
static int	has_content_around_pipe(char *input, int pipe_pos)
{
	return (has_content_before(input, pipe_pos)
		&& has_content_after(input, pipe_pos));
}

/* Checks if the pipe is not followed by another pipe and is surrounded by content */
static int	check_pipe_position(char *input, int i)
{
	int		next_non_space;

	next_non_space = i + 1;
	while (input[next_non_space] && ft_isspace(input[next_non_space]))
		next_non_space++;
	if (input[next_non_space] == '|')
		return (0);
	if (!has_content_around_pipe(input, i))
		return (0);
	return (1);
}

/* Validates the overall pipe syntax in the input line */
int	validate_pipe_syntax(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (!check_pipe_position(input, i))
				return (0);
		}
		i++;
	}
	return (1);
}
