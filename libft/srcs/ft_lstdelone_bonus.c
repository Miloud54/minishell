/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:28:23 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:26:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

void	del_content(void *content)
{
	free(content);
}

/*#include <stdio.h>
int	main(void)
{
	t_list *node;
	char *str;

	str = ft_strdup("À supprimer");
	if (!str)
		return (1);

	node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		return (1);
	}
	printf("Avant : %s\n", (char *)node->content);
	ft_lstdelone(node, del_content);
	printf("Après : supprimé\n");
	return (0);
}*/
