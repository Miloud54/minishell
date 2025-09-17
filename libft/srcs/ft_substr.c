/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:47:03 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:59:50 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*#include <stdio.h>

int	main(void)
{
		const char *src = "j'ai faim";
		char *new;

		new = ft_substr(src, 5, 5);
		printf("%s\n", new);
		free(new);
		new = ft_substr(src, 3, 3);
		printf("%s\n", new);
		free(new);
		new = ft_substr(src, 100, 5);
		printf("%s\n", new);
		free(new);
		new = ft_substr(src, 5, 0);
		printf("%s\n", new);
		free(new);
		return (0);
}*/