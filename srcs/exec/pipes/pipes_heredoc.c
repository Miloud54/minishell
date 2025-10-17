/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:30 by edidier           #+#    #+#             */
/*   Updated: 2025/10/18 17:22:00 by bde-la-p        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipeline_heredocs(t_cmd **cmds, int cmd_count, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count)
	{
		j = 0;
		while (j < cmds[i]->redirect_count)
		{
			if (cmds[i]->redirects[j].type == TOKEN_REDIR_HEREDOC)
				if (setup_heredoc(&cmds[i]->redirects[j], data) == -1)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
