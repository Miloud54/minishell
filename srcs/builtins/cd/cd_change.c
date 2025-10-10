/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:46 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 13:55:27 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dir_error(const char *path, const char *orig, t_data *d,
		char *oldpwd)
{
	if (orig)
		print_cd_error(orig);
	else
		print_cd_error(path);
	d->exit_status = 1;
	free(oldpwd);
}

int	change_directory(const char *path, const char *orig_arg, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;

	if (is_not_directory(path, data))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		change_dir_error(path, orig_arg, data, oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		print_cd_error(path);
		data->exit_status = 1;
		free(oldpwd);
		return (1);
	}
	update_env_var(&data->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	update_env_var(&data->envp, "PWD", newpwd);
	free(newpwd);
	data->exit_status = 0;
	return (0);
}
