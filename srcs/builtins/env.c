/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:42:54 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/15 17:54:58 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_args(t_cmd *cmd, t_data *data)
{
	if (!cmd->args[1])
		return (1);
	if (ft_strcmp(cmd->args[1], "-i") == 0)
	{
		data->exit_status = 0;
		return (0);
	}
	printf("env: '%s': No such file or directory\n", cmd->args[1]);
	data->exit_status = 127;
	return (0);
}

static int	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (g_signal_status == SIGINT)
			return (0);
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

void	ft_env(t_data *data, t_cmd *cmd)
{
	if (!data->envp)
		return ((void)(data->exit_status = 1));
	if (!handle_args(cmd, data))
		return ;
	if (!print_env(data->envp))
		return ((void)(data->exit_status = 130));
	data->exit_status = 0;
}
