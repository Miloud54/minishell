/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:55:54 by edidier           #+#    #+#             */
/*   Updated: 2025/10/17 17:03:46 by emiliedidie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cleanup_heredoc_tmpfile(char **path)
{
	if (!path || !*path)
		return ;
	unlink(*path);
	free(*path);
	*path = NULL;
}

int	create_heredoc_tmpfile(char **path)
{
	char	template[sizeof("/tmp/minishell_hdXXXXXX")];
	int		fd;

	ft_strlcpy(template, "/tmp/minishell_hdXXXXXX", sizeof(template));
	fd = mkstemp(template);
	if (fd == -1)
		return (-1);
	*path = ft_strdup(template);
	if (!*path)
	{
		close(fd);
		unlink(template);
		return (-1);
	}
	return (fd);
}
