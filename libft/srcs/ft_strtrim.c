/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:56:53 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:01:51 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new = malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1 + start, end - start + 1);
	return (new);
}
/*#include <stdio.h>

int	main(void)
{
	char *str = "..Hola--";
	char *set = ".-";
	char *res;

	res = ft_strtrim(str, set);
	printf("%s\n", res);
	return (0);
}*/