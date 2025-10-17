/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:00:00 by bde-la-p         #+#    #+#             */
/*   Updated: 2025/10/18 17:22:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cleanup_tmpfile(char **path)
{
	if (!path || !*path)
		return ;
	unlink(*path);
	free(*path);
	*path = NULL;
}

static int	create_tmpfile(char **path)
{
	char	template[] = "/tmp/minishell_hdXXXXXX";
	int		fd;

	fd = mkstemp(template);
	if (fd == -1)
		return (-1);
	*path = ft_strdup(template);
	if (!*path)
	{
		close(fd);
		unlink(template);
		return (-1);
	}
	return (fd);
}

int	setup_heredoc(t_redirect *redirect, t_data *data)
{
	char	*tmp_path;
	int		fd;

	fd = create_tmpfile(&tmp_path);
	if (fd == -1)
		return (-1);
	if (read_heredoc_input(fd, redirect->file, data,
			!redirect->heredoc_quoted) == -1)
	{
		close(fd);
		cleanup_tmpfile(&tmp_path);
		data->exit_status = 130;
		return (-1);
	}
	close(fd);
	if (redirect->heredoc_tmpfile)
		cleanup_tmpfile(&redirect->heredoc_tmpfile);
	redirect->heredoc_tmpfile = tmp_path;
	redirect->heredoc_fd = -1;
	return (0);
}

int	handle_heredoc_redirect(t_redirect *redirect, t_data *data)
{
	int	fd;

	if (!redirect->heredoc_tmpfile)
	{
		if (setup_heredoc(redirect, data) == -1)
			return (-1);
		if (!redirect->heredoc_tmpfile)
			return (-1);
	}
	fd = open(redirect->heredoc_tmpfile, O_RDONLY);
	if (fd == -1)
 	{
 		perror("open");
 		data->exit_status = 1;
 		cleanup_tmpfile(&redirect->heredoc_tmpfile);
 		return (-1);
 	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		data->exit_status = 1;
		return (-1);
	}
	close(fd);
	cleanup_tmpfile(&redirect->heredoc_tmpfile);
	redirect->heredoc_fd = -1;
	return (0);
}
