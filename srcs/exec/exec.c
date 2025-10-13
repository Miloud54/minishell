/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:28 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 14:06:04 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable(char *cmd, char **envp)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			else
				return (NULL);
		}
		return (NULL);
	}
	return (search_path_in_env(cmd, envp));
}

static int	handle_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

static int	handle_cmd_with_slash(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (access(cmd, F_OK) == 0)
	{
		ft_putendl_fd(": Permission denied", 2);
		return (126);
	}
	else
	{
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
}

static int	handle_path_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

int	execute_single_command(t_cmd *cmd, t_data *data)
{
	char	*cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		data->exit_status = 127;
		return (127);
	}
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(data, cmd);
		return (data->exit_status);
	}
	char *(path_env) = get_env_var(data->envp, "PATH");
	if ((!path_env || path_env[0] == '\0') && !ft_strchr(cmd->args[0], '/'))
	{
		data->exit_status = handle_path_error(cmd->args[0]);
		return (127);
	}
	cmd_path = find_executable(cmd->args[0], data->envp);
	if (!cmd_path)
	{
		if (ft_strchr(cmd->args[0], '/'))
			data->exit_status = handle_cmd_with_slash(cmd->args[0]);
		else
			data->exit_status = handle_cmd_not_found(cmd->args[0]);
		return (data->exit_status);
	}
	return (run_external_command(cmd_path, cmd, data));
}
