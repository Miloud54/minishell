/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:00:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/13 18:00:00 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_execve_error(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
}

static void	handle_cmd_not_found(t_cmd *cmd, t_data *data)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			exit_child(data, 126);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			exit_child(data, 127);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	exit_child(data, 127);
}

static char	*get_cmd_path(t_cmd *cmd, t_data *shell_data)
{
	char	*path_env;
	char	*path;

	path_env = get_env_var(shell_data->envp, "PATH");
	if ((!path_env || path_env[0] == '\0') && !ft_strchr(cmd->args[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit_child(shell_data, 127);
	}
	path = find_executable(cmd->args[0], shell_data->envp);
	if (!path)
		handle_cmd_not_found(cmd, shell_data);
	return (path);
}

void	exec_external(t_cmd *cmd, t_data *shell_data)
{
	char	*path;

	if (!cmd->args[0])
		exit_child(shell_data, 0);
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(shell_data, 127);
	}
	path = get_cmd_path(cmd, shell_data);
	close_backup_fds(shell_data);
	if (execve(path, cmd->args, shell_data->envp) == -1)
	{
		print_execve_error(path);
		free(path);
		exit_child(shell_data, 126);
	}
	free(path);
}
