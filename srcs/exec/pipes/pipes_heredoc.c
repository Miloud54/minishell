/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:30 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 17:07:45 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredocs_tmpfile(char **tmp_filename)
{
	char	*pid_str;
	int		fd;

	pid_str = ft_itoa(getpid());
	*tmp_filename = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
	free(pid_str);
	if (!*tmp_filename)
		return (-1);
	fd = open(*tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		free(*tmp_filename);
	return (fd);
}

static int	handle_heredoc(t_cmd *cmd, int j, t_data *data)
{
	int		tmp_fd;
	char	*tmp_filename;

	tmp_fd = open_heredocs_tmpfile(&tmp_filename);
	if (tmp_fd == -1)
		return (-1);
	if (write_heredoc_to_file(tmp_fd, cmd->redirects[j].file, data) == -1)
	{
		close(tmp_fd);
		unlink(tmp_filename);
		free(tmp_filename);
		return (-1);
	}
	close(tmp_fd);
	cmd->redirects[j].heredoc_fd = open(tmp_filename, O_RDONLY);
	unlink(tmp_filename);
	free(tmp_filename);
	if (cmd->redirects[j].heredoc_fd == -1)
		return (-1);
	return (0);
}

int	setup_pipeline_heredocs(t_cmd **cmds, int cmd_count, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count)
	{
		j = 0;
		while (j < cmds[i]->redirect_count)
		{
			if (cmds[i]->redirects[j].type == TOKEN_REDIR_HEREDOC)
				if (handle_heredoc(cmds[i], j, data) == -1)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
