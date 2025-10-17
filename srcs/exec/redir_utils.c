/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:46:46 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 19:22:55 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (errno == EISDIR)
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

static void	cleanup_heredoc_tmpfile(t_redirect *redir)
{
	if (!redir->heredoc_tmpfile)
		return ;
	unlink(redir->heredoc_tmpfile);
	free(redir->heredoc_tmpfile);
	redir->heredoc_tmpfile = NULL;
}

int	handle_in_redir(t_redirect *redir, t_data *data)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		print_redir_error(redir->file);
		data->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_out_redir(t_redirect *redir, t_data *data)
{
	int	flags;
	int	fd;

	if (redir->type == TOKEN_REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->file, flags, 0644);
	if (fd == -1)
	{
		print_redir_error(redir->file);
		data->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redir(t_redirect *redir, t_data *data)
{
	int	fd;

	if (!redir->heredoc_tmpfile)
	{
		if (setup_heredoc(redir, data) == -1)
			return (-1);
		if (!redir->heredoc_tmpfile)
			return (-1);
	}
	fd = open(redir->heredoc_tmpfile, O_RDONLY);
	if (fd == -1)
	{
		print_redir_error(redir->heredoc_tmpfile);
		data->exit_status = 1;
		cleanup_heredoc_tmpfile(redir);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		data->exit_status = 1;
		close(fd);
		cleanup_heredoc_tmpfile(redir);
		return (-1);
	}
	close(fd);
	cleanup_heredoc_tmpfile(redir);
	redir->heredoc_fd = -1;
	return (0);
}
