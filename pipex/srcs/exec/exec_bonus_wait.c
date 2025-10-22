/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus_wait.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:17:58 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 18:18:32 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static void	update_status(int status, int *last_status, int *has_127)
{
	*last_status = status;
	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		*has_127 = 1;
}

static void	wait_children_loop(int children_count, int *last_status,
		int *has_127)
{
	int		status;
	pid_t	finished_child;
	int		i;

	i = 0;
	while (i < children_count)
	{
		finished_child = wait(&status);
		if (finished_child > 0)
		{
			update_status(status, last_status, has_127);
			i++;
		}
		else
		{
			perror("wait failed");
			break ;
		}
	}
}

int	wait_all_children(int children_count)
{
	int	last_status;
	int	has_127;

	last_status = 0;
	has_127 = 0;
	wait_children_loop(children_count, &last_status, &has_127);
	if (has_127)
		return (127);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}
