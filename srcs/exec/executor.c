/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:43 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 15:05:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmds(t_cmd **cmds, int cmd_count, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!cmds || cmd_count == 0)
		return (0);
	if (cmd_count == 1)
	{
		if (backup_std_fds(data) == 0)
		{
			if (setup_redirections(cmds[0], data) == 0)
				exit_code = execute_single_command(cmds[0], data);
			else
				exit_code = 1;
			restore_std_fds(data);
		}
		else
			exit_code = 1;
	}
	else
		exit_code = execute_pipeline(cmds, cmd_count, data);
	if (exit_code >= 0)
		data->exit_status = exit_code;
	return (exit_code);
}
