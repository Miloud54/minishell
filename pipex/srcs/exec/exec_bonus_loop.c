/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:44:34 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 17:51:56 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

int	create_pipe(int i, int cmd_count, int pipe_fd[2])
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
	}
	return (0);
}

int	pipex_loop(t_pipex *pipex, char **envp)
{
	int				pipe_fd[2];
	int				i;
	int				prev_pipe;
	t_exec_data		data;
	t_child_args	args;

	i = 0;
	prev_pipe = -1;
	while (i < pipex->cmd_count)
	{
		create_pipe(i, pipex->cmd_count, pipe_fd);
		args.pipex = pipex;
		args.data = &data;
		args.i = i;
		args.envp = envp;
		args.prev_pipe = prev_pipe;
		args.pipe_fd[0] = pipe_fd[0];
		args.pipe_fd[1] = pipe_fd[1];
		pipex_child(&args);
		prev_pipe = handle_parent(pipe_fd, prev_pipe, i == pipex->cmd_count
				- 1);
		i++;
	}
	return (wait_all_children(pipex->cmd_count));
}
