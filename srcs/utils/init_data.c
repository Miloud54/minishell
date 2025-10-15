/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:03:06 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/15 18:13:59 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_envp(char **envp)
{
	int	counter;

	counter = 0;
	while (envp[counter])
		counter++;
	return (counter);
}

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		count;
	int		i;

	if (!envp)
		return (NULL);
	count = count_envp(envp);
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

static char	*init_env_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit("Failed to get current directory", 1);
	if (update_env_var(&data->envp, "PWD", cwd))
	{
		free(cwd);
		error_exit("Failed to set PWD", 1);
	}
	if (update_env_var(&data->envp, "OLDPWD", cwd))
	{
		free(cwd);
		error_exit("Failed to set OLDPWD", 1);
	}
	return (cwd);
}

static void	init_pwd_values(t_data *data, char *cwd)
{
	data->pwd = ft_strdup(cwd);
	if (!data->pwd)
	{
		free(cwd);
		error_exit("Failed to duplicate PWD", 1);
	}
	data->oldpwd = ft_strdup(cwd);
	if (!data->oldpwd)
	{
		free(data->pwd);
		free(cwd);
		error_exit("Failed to duplicate OLDPWD", 1);
	}
}

void	init_data(t_data *data, char **envp)
{
	char	*cwd;

	data->exit_status = 0;
	data->stdin_backup = -1;
	data->stdout_backup = -1;
	data->envp = copy_envp(envp);
	if (!data->envp)
		error_exit("Failed to copy environnement", 1);
	cwd = init_env_pwd(data);
	init_pwd_values(data, cwd);
	free(cwd);
}
