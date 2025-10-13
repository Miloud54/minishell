/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:25:46 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:45:59 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipe_input(int cmd_index, int prev_pipe)
{
	if (cmd_index == 0)
		return ;
	if (dup2(prev_pipe, STDIN_FILENO) == -1)
	{
		perror("dup2 prev_pipe");
		exit(127);
	}
	close(prev_pipe);
}

static void	setup_pipe_output(int cmd_index, int cmd_count, int pipe_fd[2])
{
	if (cmd_index == cmd_count - 1)
		return ;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe_fd[1]");
		exit(127);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	execute_piped_command(t_cmd *cmd, t_pipe_data *data, t_data *shell_data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipe_input(data->cmd_index, data->prev_pipe);
	setup_pipe_output(data->cmd_index, data->cmd_count, data->pipe_fd);
	if (setup_redirections(cmd, shell_data) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(shell_data, cmd);
		exit(shell_data->exit_status);
	}
	exec_external(cmd, shell_data);
}
