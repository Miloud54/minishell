/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:57:35 by edidier           #+#    #+#             */
/*   Updated: 2025/07/23 17:46:49 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	ft_init_pipex(&pipex);
	ft_check_args_bonus(ac, av, &pipex);
	ft_parse_args_bonus(&pipex, av, ac);
	ft_parse_cmds(&pipex, av, ac, envp);
	ft_exec_bonus(&pipex, envp);
	free_pipex(&pipex);
	return (0);
}
