/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:03:33 by edidier           #+#    #+#             */
/*   Updated: 2025/09/17 18:37:09 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	return (ft_strncmp(line, limiter, len) == 0 && ft_strlen(line) == len);
}

void	write_heredoc_line(int pipe_fd, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	line[len - 1] = '\n';
	write(pipe_fd, line, len);
}

void	read_and_write_heredoc(int pipe_fd, char *limiter)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	ft_printf("pipe heredoc> ");
	line = get_next_line(0, &tmp);
	while (line != NULL)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipe_fd, line);
		free(line);
		ft_printf("pipe heredoc> ");
		line = get_next_line(0, &tmp);
	}
	free_gnl_tmp(&tmp);
}

void	handle_heredoc(char **av, t_pipex *pipex)
{
	int	pipe_fd[2];

	pipex->here_doc = BOOL_TRUE;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	read_and_write_heredoc(pipe_fd[1], av[2]);
	close(pipe_fd[1]);
	pipex->in_fd = pipe_fd[0];
}
