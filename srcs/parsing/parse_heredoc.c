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
	// Remove newline from line if present
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

	// Expand variables in heredoc content
	expanded = expand_variables(line, data);
	if (expanded)
	{
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	else
	{
		// Si pas d'expansion, écrire la ligne originale
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

int	setup_heredoc_at_parse(t_redirect *redirect, t_data *data)
{
	int		pipe_fd[2];
	char	*line;
	char	*prompt;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	prompt = ft_strjoin(redirect->file, "> ");
	if (!prompt)
		prompt = ft_strdup("> ");
	// Lire directement dans le terminal principal (pas de fork)
	while (1)
	{
		line = readline(prompt);
		if (!line) // Ctrl+D
		{
			printf("\n");
			break ;
		}
		if (is_delimiter_parse(line, redirect->file))
		{
			free(line);
			break ;
		}
		write_to_pipe(pipe_fd[1], line, data);
		free(line);
	}
	close(pipe_fd[1]);
	redirect->heredoc_fd = pipe_fd[0];
	if (prompt)
		free(prompt);
	return (0);
}

int	write_heredoc_to_file(int fd, char *delimiter, t_data *data)
{
	char	*line;
	char	*prompt;

	prompt = ft_strjoin(delimiter, "> ");
	if (!prompt)
		prompt = ft_strdup("> ");
	while (1)
	{
		line = readline(prompt);
		if (!line) // Ctrl+D
		{
			printf("\n");
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
	if (prompt)
		free(prompt);
	return (0);
}
