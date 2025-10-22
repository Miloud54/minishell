/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:00:02 by edidier           #+#    #+#             */
/*   Updated: 2025/10/21 14:23:07 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	write_heredoc_tmp(t_redirect *redirect, t_data *data,
		char **tmp_path)
{
	int	fd;

	fd = create_heredoc_tmpfile(tmp_path);
	if (fd == -1)
		return (-1);
	if (read_heredoc_input(fd, redirect->file, data,
			!redirect->heredoc_quoted) == -1)
	{
		close(fd);
		cleanup_heredoc_tmpfile(tmp_path);
		data->exit_status = 130;
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_heredoc(t_redirect *redirect, t_data *data)
{
	char	*tmp_path;

	if (write_heredoc_tmp(redirect, data, &tmp_path) == -1)
		return (-1);
	if (redirect->heredoc_tmpfile)
		cleanup_heredoc_tmpfile(&redirect->heredoc_tmpfile);
	redirect->heredoc_tmpfile = tmp_path;
	redirect->heredoc_fd = -1;
	return (0);
}
