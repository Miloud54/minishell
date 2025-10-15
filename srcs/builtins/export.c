/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:43:08 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/15 18:32:41 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Checks if the given string is a valid identifier for export (letters, digits,
_, not starting with digit, stops at '=') */
static int	is_valid_identifier_for_export(const char *str)
{
	int	i;

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

static void	remove_exported_var(char *arg, t_data *data)
{
	int		name_len;
	int		k;

	char *(eq) = ft_strchr(arg, '=');
	if (eq)
		name_len = (int)(eq - arg);
	else
		name_len = (int)ft_strlen(arg);
	int (j) = 0;
	while (data->envp && data->envp[j])
	{
		if (ft_strncmp(data->envp[j], arg, name_len) == 0
			&& (data->envp[j][name_len] == '='
			|| data->envp[j][name_len] == '\0'))
		{
			free(data->envp[j]);
			k = j - 1;
			while (data->envp[++k])
				data->envp[k] = data->envp[k + 1];
			j--;
		}
		j++;
	}
}

static int	handle_export_arg(char *arg, t_data *data)
{
	if (ft_strcmp(arg, "=") == 0)
	{
		printf("minishell: export: `=': not a valid identifier\n");
		return (1);
	}
	if (!is_valid_identifier_for_export(arg))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	remove_exported_var(arg, data);
	add_or_update_env(data, arg);
	return (0);
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

	sort_env(envp);
	i = 0;
	while (envp && envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			printf("export %.*s=\"%s\"\n", (int)(equal - envp[i]), envp[i],
				equal + 1);
		else
			printf("export %s\n", envp[i]);
		i++;
	}
}

/* Builtin export: adds/modifies env variables or prints them if no args */
void	ft_export(t_cmd *cmd, t_data *data)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!cmd->args[1])
	{
		print_export_env(data->envp);
		data->exit_status = 0;
		return ;
	}
	while (cmd->args[++i])
		error |= handle_export_arg(cmd->args[i], data);
	data->exit_status = error;
}
