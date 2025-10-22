/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:22:02 by edidier           #+#    #+#             */
/*   Updated: 2025/07/23 17:28:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_cmd_paths(t_pipex *pipex)
{
	int	i;

	if (!pipex->cmd_paths)
		return ;
	i = 0;
	while (i < pipex->cmd_count)
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	pipex->cmd_paths = NULL;
}

static void	free_cmd_args(t_pipex *pipex)
{
	int	i;

	if (!pipex->cmd_args)
		return ;
	i = 0;
	while (i < pipex->cmd_count)
	{
		ft_free_split(&pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	pipex->cmd_args = NULL;
}

void	free_pipex(t_pipex *pipex)
{
	free_cmd_paths(pipex);
	free_cmd_args(pipex);
	if (pipex->in_fd > 2)
		close(pipex->in_fd);
	if (pipex->out_fd > 2)
		close(pipex->out_fd);
}
