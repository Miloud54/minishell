/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:00:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/09/30 17:00:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_delimiter(char *line, char *delimiter)
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
	
	return (len_line == len_delim && ft_strncmp(line, delimiter, len_delim) == 0);
}

static void	write_heredoc_line(int fd, char *line, t_data *data)
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

static void	read_heredoc_input(int write_fd, char *delimiter, t_data *data)
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
			break;
		}
		
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break;
		}
		
		write_heredoc_line(write_fd, line, data);
		free(line);
	}
	
	if (prompt)
		free(prompt);
}

int	setup_heredoc(t_redirect *redirect, t_data *data)
{
	int	pipe_fd[2];
	pid_t	pid;
	int	status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	
	if (pid == 0) // Child process - read heredoc input
	{
		close(pipe_fd[0]);
		read_heredoc_input(pipe_fd[1], redirect->file, data);
		close(pipe_fd[1]);
		exit(0);
	}
	else // Parent process
	{
		close(pipe_fd[1]);
		wait(&status);
		redirect->heredoc_fd = pipe_fd[0];
		return (0);
	}
}

int	handle_heredoc_redirect(t_redirect *redirect, t_data *data)
{
	if (redirect->heredoc_fd == -1)
	{
		if (setup_heredoc(redirect, data) == -1)
			return (-1);
	}
	
	if (dup2(redirect->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	
	return (0);
}
