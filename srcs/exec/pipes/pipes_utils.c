/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:24:13 by edidier           #+#    #+#             */
/*   Updated: 2025/10/15 18:21:23 by edidier          ###   ########.fr       */
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

static void	update_wait_context(t_wait_context *context, pid_t waited_pid,
		int status)
{
	if (!(context->last_found) && waited_pid == context->last_pid)
	{
		context->last_status = status;
		context->last_found = 1;
	}
	else if (!(context->last_found) && context->i == context->cmd_count - 1)
		context->last_status = status;
	else if (context->last_found == 0)
		context->last_status = status;
}

int	wait_all_pipeline_children(int cmd_count, pid_t last_pid)
{
	int				status;
	pid_t			waited_pid;
	t_wait_context	context;

	context.last_status = 0;
	context.printed_quit = 0;
	context.last_found = (last_pid <= 0);
	context.cmd_count = cmd_count;
	context.last_pid = last_pid;
	context.i = 0;
	while (context.i < context.cmd_count)
	{
		waited_pid = wait(&status);
		if (waited_pid == -1)
			continue ;
		handle_signal_status(status, &context.printed_quit);
		update_wait_context(&context, waited_pid, status);
		context.i++;
	}
	if (WIFEXITED(context.last_status))
		return (WEXITSTATUS(context.last_status));
	if (WIFSIGNALED(context.last_status))
		return (128 + WTERMSIG(context.last_status));
	return (1);
}
