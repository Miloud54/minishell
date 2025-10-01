/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:43 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 15:54:34 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_cmd **commands, int cmd_count, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!commands || cmd_count == 0)
		return (0);
	if (cmd_count == 1)
	{
		if (backup_std_fds(data) == 0)
		{
			if (setup_redirections(commands[0], data) == 0)
				exit_code = execute_single_command(commands[0], data);
			else
				exit_code = 1;
			restore_std_fds(data);
		}
		else
			exit_code = 1;
	}
	else
	{
		exit_code = execute_pipeline(commands, cmd_count, data);
		data->exit_status = exit_code;
	}
	return (exit_code);
}
