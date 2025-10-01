/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:03:06 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 13:51:18 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_var(char **envp, char *name)
{
	int	i;
	int	name_ln;

	if (!envp || !name)
		return (NULL);
	name_ln = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_ln) == 0 && envp[i][name_ln] == '=')
			return (envp[i] + name_ln + 1);
		i++;
	}
	return (NULL);
}

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

void	init_data(t_data *data, char **envp)
{
	char	*pwd_value;

	data->exit_status = 0;
	data->stdin_backup = -1;
	data->stdout_backup = -1;
	data->envp = copy_envp(envp);
	if (!data->envp)
		error_exit("Failed to copy environnement", 1);
	pwd_value = get_env_var(data->envp, "PWD");
	if (pwd_value)
		data->pwd = ft_strdup(pwd_value);
	else
	{
		data->pwd = malloc(MAX_PATH);
		if (!data->pwd || !getcwd(data->pwd, MAX_PATH))
			error_exit("Failed to get current directory", 1);
	}
	data->oldpwd = get_env_var(data->envp, "OLDPWD");
	if (data->oldpwd)
		data->oldpwd = ft_strdup(data->oldpwd);
}
