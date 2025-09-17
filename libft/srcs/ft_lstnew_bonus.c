/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:24:25 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:02:11 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*#include <stdio.h>

int	main(void)
{
	char *str;
	t_list *node;

	str = ft_strdup("coucouuuuu");
	node = ft_lstnew(str);
	printf("%s\n", (char *)node->content);
	free(node->content);
	free(node);
	return (0);
}*/