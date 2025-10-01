/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:45:12 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 14:02:59 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Replaces the value of an existing environment variable if it matches the name
(before '=') */
int	replace_env_var(t_data *data, const char *arg, int len)
{
	int	i;

	i = 0;
	while (data->envp && data->envp[i])
	{
		if (ft_strncmp(data->envp[i], arg, len) == 0
			&& data->envp[i][len] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Adds a new environment variable at the end of the envp array */
void	add_env_var(t_data *data, const char *arg)
{
	int		env_len;
	int		i;
	char	**new_envp;

	env_len = 0;
	while (data->envp && data->envp[env_len])
		env_len++;
	new_envp = malloc(sizeof(char *) * (env_len + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (i < env_len)
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	new_envp[i + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

/* Adds or updates a variable in the environment, even if no '=' is present */
void	add_or_update_env(t_data *data, const char *arg)
{
	int		len;
	int		i;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		len = equal - arg;
		if (!replace_env_var(data, arg, len))
			add_env_var(data, arg);
	}
	else
	{
		i = 0;
		while (data->envp && data->envp[i])
		{
			if (ft_strncmp(data->envp[i], arg, ft_strlen(arg)) == 0
				&& data->envp[i][ft_strlen(arg)] == '\0')
				return ;
			i++;
		}
		add_env_var(data, arg);
	}
}

/* Sorts envp array alphabetically (simple bubble sort) */
void	sort_env(char **envp)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (envp && envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
