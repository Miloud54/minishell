/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:49:56 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(char **argv, t_data *data)
{
	char	*home;
	char	*oldpwd;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		home = get_env_var(data->envp, "HOME");
		if (!home)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (home);
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		oldpwd = get_env_var(data->envp, "OLDPWD");
		if (!oldpwd)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (oldpwd);
	}
	return (argv[1]);
}

static void	print_cd_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static int	change_directory(const char *path, t_data *data)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		print_cd_error(path);
		data->exit_status = 1;
		free(oldpwd);
		return (1);
	}
	update_env_var(&data->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	oldpwd = getcwd(NULL, 0);
	update_env_var(&data->envp, "PWD", oldpwd);
	free(oldpwd);
	data->exit_status = 0;
	return (0);
}

int	ft_cd(t_data *data, char **argv)
{
	char	*path;

	path = get_cd_path(argv, data);
	if (!path)
	{
		data->exit_status = 1;
		return (1);
	}
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	return (change_directory(path, data));
}
