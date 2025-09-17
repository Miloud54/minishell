/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:03:52 by edidier           #+#    #+#             */
/*   Updated: 2025/07/22 17:21:23 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd, char **tmp)
{
	char	*buff;
	ssize_t	r;

	r = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(*tmp, '\n') && r > 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buff[r] = '\0';
		*tmp = ft_update_tmp(*tmp, buff);
	}
	free(buff);
	if (ft_should_return(tmp, r))
		return (NULL);
	return (ft_extract_line(tmp));
}

void	free_gnl_tmp(char **tmp)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
}
