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

static int	fork_and_fill_heredoc(int *pipe_fd, t_redirect *redirect,
	t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		read_heredoc_input(pipe_fd[1], redirect->file, data);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		wait(&status);
		redirect->heredoc_fd = pipe_fd[0];
		return (0);
	}
}

int	setup_heredoc(t_redirect *redirect, t_data *data)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (fork_and_fill_heredoc(pipe_fd, redirect, data));
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
