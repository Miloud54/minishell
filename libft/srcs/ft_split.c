/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:16:41 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:00:57 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_worddup(const char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free_all(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

static int	ft_fill_tab(char **tab, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = ft_worddup(s, c);
			if (!tab[i])
			{
				ft_free_all(tab, i);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_count_word(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!ft_fill_tab(tab, s, c))
		return (NULL);
	return (tab);
}

/*#include <stdio.h>

int	main(void)
{
	char const *s = "J'adore0les0gnocchis0.";
	char **new;
	int i;

	new = ft_split(s, '0');
	i = 0;

	while (new[i])
	{
		printf("%d : %s\n", i, new[i]);
		free(new[i]);
		i++;
	}
	free(new);

	return (0);
}*/
