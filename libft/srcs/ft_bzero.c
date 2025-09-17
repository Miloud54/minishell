/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:42:18 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:02:26 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char	str1[20] = "wesh";
	char	str2[20] = "wesh";
	int		j;
	int		i;

	j = 0;
	bzero(str1, 5);
	ft_bzero(str2, 5);
	printf("str1 après bzero : ");
	i = 0;
	while (i < 20)
	{
		printf("%d ", str1[i]);
		i++;
	}
	printf("\n");
	printf("str2 après ft_bzero : ");
	i = 0;
	while (i < 20)
	{
		printf("%d ", str2[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/
