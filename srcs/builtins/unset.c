/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:37:30 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/24 15:52:06 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Checks if the given string is a valid environment variable identifier */
static int	is_valid_identifier(const char *str)
{
	int		i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Removes the variable with the given name from the environment */
static void	remove_var(t_data *data, const char *name)
{
	int		i;
	int		j;
	int		len;

	if (!data->envp)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name, len) == 0 && data->envp[i][len] == '=')
		{
			free(data->envp[i]);
			j = i;
			while (data->envp[j])
			{
				data->envp[j] = data->envp[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}

/* Builtin unset: removes one or more variables from the environment */
void	ft_unset(t_cmd *cmd, t_data *data)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	if (!cmd->args[1])
	{
		data->exit_status = 0;
		return ;
	}
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			printf("unset: '%s': not a valid identifier\n", cmd->args[i]);
			error = 1;
		}
		else
			remove_var(data, cmd->args[i]);
		i++;
	}
	data->exit_status = error;
}