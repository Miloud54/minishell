/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:41:43 by edidier           #+#    #+#             */
/*   Updated: 2025/09/17 17:47:14 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

int	open_file(char *filename, int flags, mode_t mode, char *message)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		if (flags & O_RDONLY)
		{
			perror(filename);
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
			{
				perror("/dev/null");
				exit(1);
			}
			return (fd);
		}
		else
		{
			ft_printf("%s\n", message);
			exit(1);
		}
	}
	return (fd);
}

void	ft_parse_args_bonus(t_pipex *pipex, char **av, int ac)
{
	if (pipex->here_doc)
	{
		handle_heredoc(av, pipex);
		pipex->out_fd = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644, "Error opening output file");
	}
	else
	{
		pipex->in_fd = open_file(av[1], O_RDONLY, 0644,
				"Error opening input file");
		pipex->out_fd = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644, "Error opening output file");
	}
}
