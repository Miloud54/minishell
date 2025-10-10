/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:40 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 13:58:24 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_token(const char *cdpath, int start, int end)
{
	int		len;
	char	*token;

	len = end - start;
	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, cdpath + start, len + 1);
	token[len] = '\0';
	return (token);
}

static char	*build_possible(const char *dir, const char *arg)
{
	char	*fullpath;
	char	*possible;
	int		len;

	len = ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
		fullpath = ft_strdup(dir);
	else
		fullpath = ft_strjoin(dir, "/");
	possible = ft_strjoin(fullpath, arg);
	free(fullpath);
	return (possible);
}

static char	*process_cd_entry(const char *cdpath, int start, int end,
		const char *arg)
{
	char	*token;
	char	*possible;

	token = extract_token(cdpath, start, end);
	if (!token)
		return (NULL);
	possible = build_possible(token, arg);
	free(token);
	if (!possible)
		return (NULL);
	if (access(possible, F_OK) == 0 && access(possible, X_OK) == 0)
		return (possible);
	free(possible);
	return (NULL);
}

char	*try_cdpath(const char *arg, char **envp)
{
	char	*cdpath;
	int		start;
	int		end;
	char	*res;

	cdpath = get_env_var(envp, "CDPATH");
	if (!cdpath || arg[0] == '/' || arg[0] == '.')
		return (NULL);
	start = 0;
	while (cdpath[start])
	{
		end = start;
		while (cdpath[end] && cdpath[end] != ':')
			end++;
		res = process_cd_entry(cdpath, start, end, arg);
		if (res)
			return (res);
		if (cdpath[end] == ':')
			end++;
		start = end;
	}
	return (NULL);
}
