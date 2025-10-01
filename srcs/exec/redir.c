/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:57 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 16:14:04 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_one_redirection(t_redirect *redir, t_data *data)
{
	if (redir->type == TOKEN_REDIR_IN)
	{
		if (handle_in_redir(redir, data) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_REDIR_OUT
		|| redir->type == TOKEN_REDIR_APPEND)
	{
		if (handle_out_redir(redir, data) == -1)
			return (-1);
	}
	else if (redir->type == TOKEN_REDIR_HEREDOC)
	{
		if (handle_heredoc_redir(redir, data) == -1)
			return (-1);
	}
	return (0);
}

int	setup_redirections(t_cmd *cmd, t_data *data)
{
	int			i;
	t_redirect	*redir;

	i = 0;
	if (!cmd || !cmd->redirects)
		return (0);
	while (i < cmd->redirect_count)
	{
		redir = &cmd->redirects[i];
		if (handle_one_redirection(redir, data) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	restore_std_fds(t_data *data)
{
	if (data->stdin_backup != -1)
	{
		dup2(data->stdin_backup, STDIN_FILENO);
		close(data->stdin_backup);
		data->stdin_backup = -1;
	}
	if (data->stdout_backup != -1)
	{
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->stdout_backup);
		data->stdout_backup = -1;
	}
}

int	backup_std_fds(t_data *data)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdin_backup == -1 || data->stdout_backup == -1)
	{
		perror("backup fds");
		return (-1);
	}
	return (0);
}
