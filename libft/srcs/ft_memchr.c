/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:22:37 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:26:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char				data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	const unsigned int	size = 9;
	void				*found;
	void				*found1;

	found = memchr(data, 4, size);
	found1 = ft_memchr(data, 4, size);
	printf("%s\n", (found != NULL ? "found" : "not found"));
	printf("%s\n", (found1 != NULL ? "found" : "not found"));
	found = memchr(data, 44, size);
	found1 = ft_memchr(data, 44, size);
	printf("%s\n", (found != NULL ? "found" : "not found"));
	printf("%s\n", (found1 != NULL ? "found" : "not found"));
	return (0);
}*/
