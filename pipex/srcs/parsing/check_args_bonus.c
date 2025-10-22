/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:07:07 by edidier           #+#    #+#             */
/*   Updated: 2025/09/17 18:44:57 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static void	heredoc_check(int ac, char **av, t_pipex *pipex)
{
	if (ac < 6)
	{
		ft_printf("Usage: ./pipex here_doc LIMITER cmd cmd1 ... file\n");
		exit(1);
	}
	if (!av[2] || av[2][0] == '\0')
	{
		ft_printf("LIMITER can't be empty\n");
		exit(1);
	}
	pipex->here_doc = BOOL_TRUE;
	validate_output_file(av[ac - 1]);
}

static void	normal_files_check(int ac, char **av, t_pipex *pipex)
{
	pipex->in_fd = open_file(av[1], O_RDONLY, 0, "Failed to open input file");
	pipex->out_fd = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644,
			"Failed to open output file");
}

void	ft_check_args_bonus(int ac, char **av, t_pipex *pipex)
{
	if (ac < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... outfile\n");
		ft_printf("   or: ./pipex here_doc LIMITER cmd cmd1 ... file\n");
		exit(1);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
		heredoc_check(ac, av, pipex);
	else
		normal_files_check(ac, av, pipex);
}
