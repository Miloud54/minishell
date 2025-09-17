/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:45:16 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:01:10 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_ptr(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_update_tmp(char *tmp, char *buff)
{
	char	*joined;

	if (!buff)
		return (tmp);
	if (!tmp)
		return (ft_strdup(buff));
	joined = ft_strjoin(tmp, buff);
	free(tmp);
	return (joined);
}

char	*ft_extract_line(char **tmp)
{
	char	*newline;
	char	*line;
	char	*rest;

	if (!tmp || !*tmp || (*tmp)[0] == '\0')
		return (NULL);
	newline = ft_strchr(*tmp, '\n');
	if (!newline)
	{
		line = ft_strdup(*tmp);
		ft_free_ptr(tmp);
		return (line);
	}
	line = ft_substr(*tmp, 0, newline - *tmp + 1);
	rest = ft_strdup(newline + 1);
	if (!rest)
		return (free(line), ft_free_ptr(tmp), NULL);
	free(*tmp);
	*tmp = rest;
	return (line);
}

int	ft_should_return(char **tmp, ssize_t r)
{
	if (r < 0 || tmp == NULL || *tmp == NULL || (*tmp)[0] == '\0')
		return (ft_free_ptr(tmp), 1);
	return (0);
}
