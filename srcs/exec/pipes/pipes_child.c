/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:25:46 by edidier           #+#    #+#             */
/*   Updated: 2025/10/06 17:17:31 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exec_external(t_cmd *cmd, t_data *shell_data)
{
	char	*path;
	char	*path_env;

	path_env = get_env_var(shell_data->envp, "PATH");
	if ((!path_env || path_env[0] == '\0') && !ft_strchr(cmd->args[0], '/'))
	{
		printf("minishell: %s: No such file or directory\n", cmd->args[0]);
		exit(127);
	}
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	path = find_executable(cmd->args[0], shell_data->envp);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (access(cmd->args[0], F_OK) == 0)
				printf("minishell: %s: Permission denied\n", cmd->args[0]);
			else
				printf("minishell: %s: No such file or directory\n", cmd->args[0]);
		}
		else
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
		}
		exit(127);
	}
	if (execve(path, cmd->args, shell_data->envp) == -1)
	{
		struct stat st;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			fprintf(stderr, "minishell: %s: Is a directory\n", path);
		else if (errno == EACCES)
			fprintf(stderr, "minishell: %s: Permission denied\n", path);
		else
			fprintf(stderr, "minishell: %s: %s\n", path, strerror(errno));
		free(path);
		exit(126);
	}
	free(path);
}

void	execute_piped_command(t_cmd *cmd, t_pipe_data *data, t_data *shell_data)
{
	setup_pipe_input(data->cmd_index, data->prev_pipe);
	setup_pipe_output(data->cmd_index, data->cmd_count, data->pipe_fd);
	if (setup_redirections(cmd, shell_data) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(shell_data, cmd);
		exit(shell_data->exit_status);
	}
	exec_external(cmd, shell_data);
}
