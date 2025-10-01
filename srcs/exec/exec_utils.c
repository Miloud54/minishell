/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:21:47 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 17:17:04 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path_in_env(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	int (i) = 0;
	path_env = get_env_var(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_argv(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_argv(paths);
	return (NULL);
}

static void	child_execve(char *cmd_path, t_cmd *cmd, t_data *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, cmd->args, data->envp);
	perror("minishell: execve");
	exit(127);
}

static int	parent_wait_and_status(pid_t pid, char *cmd_path, t_data *data)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	free(cmd_path);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	return (data->exit_status);
}

int	run_external_command(char *cmd_path, t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(cmd_path);
		data->exit_status = 1;
		return (1);
	}
	if (pid == 0)
		child_execve(cmd_path, cmd, data);
	return (parent_wait_and_status(pid, cmd_path, data));
}
