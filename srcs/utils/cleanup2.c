/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:00:37 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 13:51:10 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cmd_args(t_cmd *cmd)
{
	int	i;

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

static void	free_redirect(t_redirect *redirect)
{
	if (redirect->file)
	{
		free(redirect->file);
		redirect->file = NULL;
	}
	if (redirect->heredoc_fd != -1)
	{
		close(redirect->heredoc_fd);
		redirect->heredoc_fd = -1;
	}
	cleanup_heredoc_tmpfile(&redirect->heredoc_tmpfile);
}

static void	free_cmd_redirects(t_cmd *cmd)
{
	int	i;

	if (!cmd->redirects || cmd->redirect_count <= 0)
		return ;
	i = 0;
	while (i < cmd->redirect_count)
	{
		free_redirect(&cmd->redirects[i]);
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (result);
}
