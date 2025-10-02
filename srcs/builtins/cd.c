/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/02 14:11:17 by edidier          ###   ########.fr       */
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

static int	is_not_directory(const char *path, t_data *data)
{
	struct stat	st;

	if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

static void	print_cd_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static int	change_directory(const char *path, const char *orig_arg,
		t_data *data)
{
	char	*oldpwd;

	if (is_not_directory(path, data))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		print_cd_error(orig_arg ? orig_arg : path);
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
	char		*expanded;
	char		*path;
	int			argc;
	int			ret;
	const char	*orig_arg = argv[1];

	expanded = NULL;
	path = NULL;
	argc = 0;
	if (argv[1] && argv[1][0] == '-' && argv[1][1] && !(argv[1][1] == '\0'
			|| (argv[1][1] == '-' && argv[1][2] == '\0')))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("cd: usage: cd [dir]\n", 2);
		data->exit_status = 1;
		return (1);
	}
	if (argv[1] && argv[1][0] == '$')
	{
		expanded = expand_env_var(argv[1], data->envp);
		if (!expanded && ft_strcmp(argv[1], "$HOME") == 0)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			data->exit_status = 1;
			return (1);
		}
	}
	if (expanded)
		path = expanded;
	else
		path = get_cd_path(argv, data);
	if (!path)
	{
		data->exit_status = 1;
		if (expanded)
			free(expanded);
		return (1);
	}
	if ((argv[1] == NULL || (argv[1] && ft_strcmp(argv[1], "~") == 0))
		&& path[0] == '\0')
	{
		data->exit_status = 0;
		if (expanded)
			free(expanded);
		return (0);
	}
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->exit_status = 1;
		if (expanded)
			free(expanded);
		return (1);
	}
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	ret = change_directory(path, orig_arg, data);
	if (expanded)
		free(expanded);
	return (ret);
}
