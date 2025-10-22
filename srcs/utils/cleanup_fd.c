/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:10:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/18 19:10:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_backup_fds(t_data *data)
{
	if (!data)
		return ;
	if (data->stdin_backup != -1)
	{
		close(data->stdin_backup);
		data->stdin_backup = -1;
	}
	if (data->stdout_backup != -1)
	{
		close(data->stdout_backup);
		data->stdout_backup = -1;
	}
}

void	exit_child(t_data *data, int status)
{
	close_backup_fds(data);
	free_data(data);
	exit(status);
}
