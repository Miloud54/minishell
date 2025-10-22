/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:30:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/09/30 11:30:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <fcntl.h>

static int	lauch_pipeline_child(t_child_args *args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		args->pipe_data->cmd_index = args->i;
		args->pipe_data->pipe_fd = args->pipe_fd;
		args->pipe_data->prev_pipe = args->prev_pipe;
		args->pipe_data->cmd_count = args->cmd_count;
		execute_piped_command(args->cmds[args->i], args->pipe_data, args->data);
	}
	return (pid);
}

static pid_t	launch_pipeline_iteration(t_iter_args *args)
{
	int				pipe_fd[2];
	pid_t			pid;
	t_pipe_data		pipe_data;
	t_child_args	child_args;

	if (create_pipe_if_needed(args->i, args->cmd_count, pipe_fd) == -1)
		return (-1);
	child_args.cmds = args->cmds;
	child_args.i = args->i;
	child_args.cmd_count = args->cmd_count;
	child_args.pipe_data = &pipe_data;
	child_args.pipe_fd = pipe_fd;
	child_args.prev_pipe = *(args->prev_pipe);
	child_args.data = args->data;
	pid = lauch_pipeline_child(&child_args);
	if (pid == -1)
		return (-1);
	*(args->prev_pipe) = handle_parent_process(pipe_fd, *(args->prev_pipe),
			(args->i == args->cmd_count - 1));
	return (pid);
}

static int	lauch_pipeline_loop(t_cmd **cmds, int cmd_count, t_data *data)
{
	int			prev_pipe;
	int			i;
	pid_t		last_pid;
	pid_t		current_pid;
	t_iter_args	args;

	prev_pipe = -1;
	last_pid = -1;
	i = 0;
	args.cmds = cmds;
	args.cmd_count = cmd_count;
	args.prev_pipe = &prev_pipe;
	args.data = data;
	while (i < cmd_count)
	{
		args.i = i;
		current_pid = launch_pipeline_iteration(&args);
		if (current_pid == -1)
			return (-1);
		if (i == cmd_count - 1)
			last_pid = current_pid;
		i++;
	}
	return (wait_all_pipeline_children(cmd_count, last_pid));
}

int	execute_pipeline(t_cmd **cmds, int cmd_count, t_data *data)
{
	if (setup_pipeline_heredocs(cmds, cmd_count, data) == -1)
		return (-1);
	return (lauch_pipeline_loop(cmds, cmd_count, data));
}
