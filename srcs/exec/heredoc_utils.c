/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:23:12 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 17:23:13 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_delimiter(char *line, char *delimiter)
{
	int	len_line;
	int	len_delim;

	if (!line || !delimiter)
		return (0);
	len_line = ft_strlen(line);
	len_delim = ft_strlen(delimiter);
	if (len_line > 0 && line[len_line - 1] == '\n')
	{
		line[len_line - 1] = '\0';
		len_line--;
	}
	return (len_line == len_delim && ft_strncmp(line, delimiter,
			len_delim) == 0);
}

void	write_heredoc_line(int fd, char *line, t_data *data, int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_variables(line, data);
		if (!expanded)
			expanded = ft_strdup("");
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	read_heredoc_input(int write_fd, char *delimiter, t_data *data,
        int expand)
{
	char	*line;
	const char	*prompt;
	prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_heredoc_line(write_fd, line, data, expand);
		free(line);
	}
}
