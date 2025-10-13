/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:24:13 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 21:26:44 by bde-la-p         ###   ########.fr       */
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

static void	update_wait_ctx(t_wait_ctx *ctx, pid_t waited_pid, int status)
{
	if (!(ctx->last_found) && waited_pid == ctx->last_pid)
	{
		ctx->last_status = status;
		ctx->last_found = 1;
	}
	else if (!(ctx->last_found) && ctx->i == ctx->cmd_count - 1)
		ctx->last_status = status;
	else if (ctx->last_found == 0)
		ctx->last_status = status;
}

int	wait_all_pipeline_children(int cmd_count, pid_t last_pid)
{
	int			status;
	pid_t		waited_pid;
	t_wait_ctx	ctx;

	ctx.last_status = 0;
	ctx.printed_quit = 0;
	ctx.last_found = (last_pid <= 0);
	ctx.cmd_count = cmd_count;
	ctx.last_pid = last_pid;
	ctx.i = 0;
	while (ctx.i < ctx.cmd_count)
	{
		waited_pid = wait(&status);
		if (waited_pid == -1)
			continue ;
		handle_signal_status(status, &ctx.printed_quit);
		update_wait_ctx(&ctx, waited_pid, status);
		ctx.i++;
	}
	if (WIFEXITED(ctx.last_status))
		return (WEXITSTATUS(ctx.last_status));
	if (WIFSIGNALED(ctx.last_status))
		return (128 + WTERMSIG(ctx.last_status));
	return (1);
}
