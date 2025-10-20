/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:00:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/10/19 15:12:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ensure_tmpfile_exists(t_redirect *redirect, t_data *data)
{
	if (redirect->heredoc_tmpfile)
		return (0);
	if (setup_heredoc(redirect, data) == -1)
		return (-1);
	if (!redirect->heredoc_tmpfile)
		return (-1);
	return (0);
}

static int	dup_tmpfile_to_stdin(int fd, t_redirect *redirect, t_data *data)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		data->exit_status = 1;
		close(fd);
		cleanup_heredoc_tmpfile(&redirect->heredoc_tmpfile);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redirect(t_redirect *redirect, t_data *data)
{
	int	fd;

	if (ensure_tmpfile_exists(redirect, data) == -1)
		return (-1);
	fd = open(redirect->heredoc_tmpfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		data->exit_status = 1;
		cleanup_heredoc_tmpfile(&redirect->heredoc_tmpfile);
		return (-1);
	}
	if (dup_tmpfile_to_stdin(fd, redirect, data) == -1)
		return (-1);
	cleanup_heredoc_tmpfile(&redirect->heredoc_tmpfile);
	redirect->heredoc_fd = -1;
	return (0);
}
