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

static int	create_pipe_if_needed(int i, int cmd_count, int pipe_fd[2])
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

static void	setup_pipe_input(int cmd_index, int prev_pipe)
{
	if (cmd_index == 0)
		return ;
	if (dup2(prev_pipe, STDIN_FILENO) == -1)
	{
		perror("dup2 prev_pipe");
		exit(127);
	}
	close(prev_pipe);
}

static void	setup_pipe_output(int cmd_index, int cmd_count, int pipe_fd[2])
{
	if (cmd_index == cmd_count - 1)
		return ;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe_fd[1]");
		exit(127);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	execute_piped_command(t_cmd *cmd, t_pipe_data *data,
		t_data *shell_data)
{
	char	*path;

	setup_pipe_input(data->cmd_index, data->prev_pipe);
	setup_pipe_output(data->cmd_index, data->cmd_count, data->pipe_fd);
	if (setup_redirections(cmd, shell_data) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(shell_data, cmd);
		exit(shell_data->exit_status);
	}
	else
	{
		path = find_executable(cmd->args[0], shell_data->envp);
		if (!path)
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		if (execve(path, cmd->args, shell_data->envp) == -1)
		{
			perror("execve");
			free(path);
			exit(127);
		}
		free(path);
	}
}

static int	handle_parent_process(int pipe_fd[2], int prev_pipe,
		int is_last_cmd)
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

static int	wait_all_pipeline_children(int cmd_count)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}



int	execute_pipeline(t_cmd **commands, int cmd_count, t_data *data)
{
	int			pipe_fd[2];
	int			prev_pipe;
	pid_t		pid;
	t_pipe_data	pipe_data;
	int			i;

	prev_pipe = -1;
	i = 0;
	if (setup_pipeline_heredocs(commands, cmd_count, data) == -1)
		return (-1);
	while (i < cmd_count)
	{
		if (create_pipe_if_needed(i, cmd_count, pipe_fd) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (pid == 0)
		{
			pipe_data.cmd_index = i;
			pipe_data.pipe_fd = pipe_fd;
			pipe_data.prev_pipe = prev_pipe;
			pipe_data.cmd_count = cmd_count;
			execute_piped_command(commands[i], &pipe_data, data);
		}
		prev_pipe = handle_parent_process(pipe_fd, prev_pipe, (i == cmd_count
					- 1));
		i++;
	}
	return (wait_all_pipeline_children(cmd_count));
}
