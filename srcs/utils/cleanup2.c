/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:00:37 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/30 16:31:27 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cmd_args(t_cmd *cmd)
{
	int		i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

static void	free_cmd_redirects(t_cmd *cmd)
{
	int		i;

	if (!cmd->redirects || cmd->redirect_count <= 0)
		return ;
	i = 0;
	while (i < cmd->redirect_count)
	{
		if (cmd->redirects[i].file)
		{
			free(cmd->redirects[i].file);
			cmd->redirects[i].file = NULL;
		}
		if (cmd->redirects[i].heredoc_fd != -1)
		{
			close(cmd->redirects[i].heredoc_fd);
			cmd->redirects[i].heredoc_fd = -1;
		}
		i++;
	}
	free(cmd->redirects);
	cmd->redirects = NULL;
	cmd->redirect_count = 0;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_cmd_args(cmd);
	free_cmd_redirects(cmd);
	free(cmd);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;

    if (!s1 || !s2)
        return (NULL);
    result = ft_strjoin(s1, s2);
    if (s1)
        free(s1);
    return (result);
}
