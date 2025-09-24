/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:43:08 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/24 18:05:32 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Checks if the given string is a valid identifier for export (letters, digits,
_, not starting with digit, stops at '=') */
static int	is_valid_identifier_for_export(const char *str)
{
	int		i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Prints all environment variables in the export format (export VAR="value") 
for POSIX style */
/* FYI : the syntax "%.*s" means to print a substring of given length, starting 
from a pointer. 
- The first arg is the number of chars before the equal sign.
- The second arg is the pointer to the string.*/
static void	print_export_env(char **envp)
{
	int		i;
	char	*equal;

	i = 0;
	while (envp && envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			printf("export %.*s=\"%s\"\n",
				(int)(equal - envp[i]), envp[i], equal + 1);
		else
			printf("export %s\n", envp[i]);
		i++;
	}
}

/* Builtin export: adds/modifies env variables or prints them if no args */
void	ft_export(t_cmd *cmd, t_data *data)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	if (!cmd->args[1])
	{
		print_export_env(data->envp);
		data->exit_status = 0;
		return ;
	}
	while (cmd->args[i])
	{
		if (!is_valid_identifier_for_export(cmd->args[i]))
		{
			printf("export: '%s': not a valid identifier\n", cmd->args[i]);
			error = 1;
		}
		else
			add_or_update_env(data, cmd->args[i]);
		i++;
	}
	data->exit_status = error;
}
