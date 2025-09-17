/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:49:19 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:59:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last_occur;

	i = 0;
	last_occur = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			last_occur = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		last_occur = (char *)&s[i];
	return (last_occur);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char    *str;
	char    *result;
	char    *result2;
	char    *noresult;

	str = "Wesh alors";
	result = strrchr(str, 'o');
	result2 = ft_strrchr(str, 'o');
	noresult = "No result";
	if (result && result2)
		printf("%s / %s", result, result2);
	else
		printf("%s", noresult);
	return (0);
}*/
