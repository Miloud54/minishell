/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:01:31 by edidier           #+#    #+#             */
/*   Updated: 2025/09/17 18:37:13 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->here_doc = BOOL_FALSE;
	pipex->is_invalid_infile = BOOL_FALSE;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_count = 0;
}
