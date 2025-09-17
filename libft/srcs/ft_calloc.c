/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:40:14 by edidier           #+#    #+#             */
/*   Updated: 2025/07/27 21:34:53 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t elementCount, size_t size)
{
	size_t	total;
	void	*ptr;

	if (elementCount == 0 || size == 0)
		return (malloc(1));
	total = elementCount * size;
	if (total / elementCount != size)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

/*#include <stdio.h>

int	main(void)
{
	size_t i;
	size_t elementCount;
	int *s1;
	int *s2;

	elementCount = 5;
	s1 = (int *)calloc(elementCount, sizeof(int));
	s2 = (int *)ft_calloc(elementCount, sizeof(int));
	i = 0;
	while (i < elementCount)
	{
		printf("calloc[%zu] = %d, ft_calloc[%zu] = %d\n", i, s1[i], i, s2[i]);
		i++;
	}
	free(s1);
	free(s2);
	return (0);
}*/