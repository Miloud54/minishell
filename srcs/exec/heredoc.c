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

static void	run_heredoc_child(int *pipe_fd, t_redirect *redirect, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	read_heredoc_input(pipe_fd[1], redirect->file, data,
		!redirect->heredoc_quoted);
	close(pipe_fd[1]);
	exit(0);
}

static int	finalize_heredoc(pid_t pid, int *pipe_fd, t_redirect *redirect,
	t_data *data)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		redirect->heredoc_fd = -1;
		data->exit_status = 130;
		g_signal_status = SIGINT;
		return (-1);
	}
	redirect->heredoc_fd = pipe_fd[0];
	return (0);
}

static int	fork_and_fill_heredoc(int *pipe_fd, t_redirect *redirect,
	t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		run_heredoc_child(pipe_fd, redirect, data);
	return (finalize_heredoc(pid, pipe_fd, redirect, data));
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
