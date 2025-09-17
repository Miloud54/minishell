/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:14:29 by edidier           #+#    #+#             */
/*   Updated: 2025/07/25 15:30:09 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

int	get_cmd_start_index(t_pipex *pipex)
{
	if (pipex->here_doc)
		return (3);
	return (2);
}

int	get_cmd_count(t_pipex *pipex, int ac)
{
	if (pipex->here_doc)
		return (ac - 4);
	return (ac - 3);
}

int	get_array_index(t_pipex *pipex, int i)
{
	int	start_index;

	start_index = get_cmd_start_index(pipex);
	return (i - start_index);
}
