/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:43 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:52:47 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_cmd **commands, int cmd_count, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!commands || cmd_count == 0)
		return (0);
	/* Pour l'instant, une seule commande (pas de pipes) */
	if (cmd_count == 1)
	{
		// Version avec redirections
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
		/* Phase 6 - Pipes implementation */
		exit_code = execute_pipeline(commands, cmd_count, data);
		data->exit_status = exit_code;
	}
	return (exit_code);
}
