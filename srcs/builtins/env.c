/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:42:54 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 13:50:01 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                             ENV - Explanation                              */
/* ************************************************************************** */

/* The 'env' command's purpose is to print all environnement variables available
in the shell. Each variable is printed on one line, as below :
KEY=value

Example:
$> env
PATH=/usr/bin:/bin
HOME=/home/user
SHELL=/bin/bash
...

The minishell version of the 'env' command doesn't require to manage args*/

/* ************************************************************************** */
/*                               ENV - Function                               */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data, t_cmd *cmd)
{
	int	i;

	if (!data->envp)
	{
		data->exit_status = 1;
		return ;
	}
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-i") == 0)
	{
		data->exit_status = 0;
		return ;
	}
	if (cmd->args[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		data->exit_status = 127;
		return ;
	}
	i = 0;
	while (data->envp[i])
	{
		if (g_signal_status == SIGINT)
		{
			data->exit_status = 130;
			return ;
		}
		printf("%s\n", data->envp[i]);
		i++;
	}
	data->exit_status = 0;
}
