/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:47:33 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 18:18:40 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	setup_input(t_pipex *pipex, int i, int prev_pipe)
{
	if (i == 0)
	{
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for input");
			exit(1);
		}
	}
	else
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for prev_pipe");
			exit(1);
		}
		close(prev_pipe);
	}
}

void	setup_output(t_pipex *pipex, int i, int pipe_fd[2])
{
	if (i == pipex->cmd_count - 1)
	{
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for output");
			exit(1);
		}
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for pipe");
			exit(1);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	execute_cmd(t_pipex *pipex, t_exec_data *data)
{
	setup_input(pipex, data->cmd_index, data->prev_pipe);
	setup_output(pipex, data->cmd_index, data->pipe_fd);
	close(pipex->in_fd);
	close(pipex->out_fd);
	if (!pipex->cmd_paths[data->cmd_index])
	{
		if (pipex->cmd_args[data->cmd_index]
			&& pipex->cmd_args[data->cmd_index][0])
			ft_printf("command not found: %s\n",
				pipex->cmd_args[data->cmd_index][0]);
		else
			ft_printf("command not found\n");
		exit(127);
	}
	if (execve(pipex->cmd_paths[data->cmd_index],
			pipex->cmd_args[data->cmd_index], data->envp) == -1)
	{
		perror("execve failed");
		exit(127);
	}
}

int	handle_parent(int pipe_fd[2], int prev_pipe, int is_last)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (!is_last)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (-1);
}
