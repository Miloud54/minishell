/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:47:43 by edidier           #+#    #+#             */
/*   Updated: 2025/10/06 17:44:47 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction a etendre aux autres builtins lorsque l'on voudra les executer

int	is_builtin_command(const char *input, char *builtin_name):
- qui vérifie si l’entrée correspond à n’importe quel builtin (exit, cd, echo,
	etc.)
- ensuite, on pourra dispatcher vers la bonne fonction builtin selon le
	nom détecté et les arguments
*/

int	is_exit_command(const char *input)
{
	int	i;

	i = 0;
	skip_spaces(input, &i);
	if (ft_strncmp(input + i, "exit", 4) == 0 && (input[i + 4] == '\0'
			|| input[i + 4] == ' '
			|| (input[i + 4] >= 9 && input[i + 4] <= 13)))
		return (1);
	return (0);
}

/* function to detext builtins */
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd, ":") == 0)
		return (true);
	if (ft_strcmp(cmd, "!") == 0)
		return (true);
	return (false);
}

void	exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd, data);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(data, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		data->exit_status = ft_pwd(cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd, data);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd, data);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(data, cmd->args);
	else if (ft_strcmp(cmd->args[0], ":") == 0)
		data->exit_status = 0;
	else if (ft_strcmp(cmd->args[0], "!") == 0)
		data->exit_status = 0;
}
