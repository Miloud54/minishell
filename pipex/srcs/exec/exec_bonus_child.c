/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:45:27 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 18:15:57 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	return (pid);
}

void	pipex_child(t_child_args *args)
{
	pid_t	pid;

	pid = create_process();
	if (pid == 0)
	{
		args->data->cmd_index = args->i;
		args->data->pipe_fd = args->pipe_fd;
		args->data->prev_pipe = args->prev_pipe;
		args->data->envp = args->envp;
		execute_cmd(args->pipex, args->data);
	}
}
