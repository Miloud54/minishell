/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:40:48 by edidier           #+#    #+#             */
/*   Updated: 2025/07/24 16:08:40 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static char	*test_path_segment(char *path, int start, int end, char *cmd)
{
	char	*path_part;
	char	*tmp;
	char	*full_path;

	if (start >= end)
		return (NULL);
	path_part = ft_substr(path, start, end - start);
	if (!path_part)
		return (NULL);
	tmp = ft_strjoin(path_part, "/");
	free(path_part);
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	if (full_path)
		free(full_path);
	return (NULL);
}

static char	*search_cmd_in_path(char *path, char *cmd)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	end = 0;
	while (path[end] != '\0')
	{
		if (path[end] == ':')
		{
			result = test_path_segment(path, start, end, cmd);
			if (result)
				return (result);
			start = end + 1;
		}
		end++;
	}
	return (test_path_segment(path, start, end, cmd));
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int	i;

	if (!cmd || !envp || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (search_cmd_in_path(envp[i] + 5, cmd));
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
