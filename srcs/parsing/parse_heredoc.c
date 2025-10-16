/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:30:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/09/30 17:30:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_delimiter_parse(char *line, char *delimiter)
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

static void	write_to_pipe(int fd, char *line, t_data *data)
{
	char	*expanded;

	expanded = expand_variables(line, data);
	if (expanded)
	{
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

static int	fill_heredoc_pipe(int write_fd, char *delimiter, t_data *data)
{
	char		*line;
	const char	*prompt;

	prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			print_heredoc_eof_warning(data, delimiter);
			break ;
		}
		if (is_delimiter_parse(line, delimiter))
		{
			free(line);
			break ;
		}
		write_to_pipe(write_fd, line, data);
		free(line);
	}
	return (0);
}

int	setup_heredoc_at_parse(t_redirect *redirect, t_data *data)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	fill_heredoc_pipe(pipe_fd[1], redirect->file, data);
	close(pipe_fd[1]);
	redirect->heredoc_fd = pipe_fd[0];
	return (0);
}

int	write_heredoc_to_file(int fd, char *delimiter, t_data *data)
{
	char		*line;
	const char	*prompt;

	prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			print_heredoc_eof_warning(data, delimiter);
			break ;
		}
		if (is_delimiter_parse(line, delimiter))
		{
			free(line);
			break ;
		}
		write_to_pipe(fd, line, data);
		free(line);
	}
	return (0);
}
