/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:24:13 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 18:18:13 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_if_needed(int i, int cmd_count, int pipe_fd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	handle_parent_process(int pipe_fd[2], int prev_pipe, int is_last_cmd)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (!is_last_cmd)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

static void	handle_signal_status(int status, int *printed_quit)
{
	int	sig;

	if (!WIFSIGNALED(status))
		return ;
	sig = WTERMSIG(status);
	if (sig == SIGQUIT && !*printed_quit)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		*printed_quit = 1;
	}
}

int	wait_all_pipeline_children(int cmd_count, pid_t last_pid)
{
	int	status;
	int	last_status;
	int	printed_quit;
	int	i;
	int	last_found;
	pid_t	waited_pid;

	last_status = 0;
	printed_quit = 0;
	last_found = (last_pid <= 0);
	i = 0;
	while (i < cmd_count)
	{
		waited_pid = wait(&status);
		if (waited_pid == -1)
			continue ;
		handle_signal_status(status, &printed_quit);
		if (!last_found && waited_pid == last_pid)
		{
			last_status = status;
			last_found = 1;
		}
		else if (!last_found && i == cmd_count - 1)
			last_status = status;
		else if (last_found == 0)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}
