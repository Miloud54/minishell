/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:52 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 17:48:28 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	ft_exec_bonus(t_pipex *pipex, char **envp)
{
	int	exit_code;

	exit_code = pipex_loop(pipex, envp);
	free_pipex(pipex);
	exit(exit_code);
}
