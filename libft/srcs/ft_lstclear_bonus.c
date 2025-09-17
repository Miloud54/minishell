/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:31:14 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 15:37:14 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !(*lst) || !del)
		return ;
	if ((*lst)->next)
		ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
/*#include <stdio.h>

void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *list = NULL;
	char *str1 = ft_strdup("Liste 1");
	char *str2 = ft_strdup("Liste 2");
	char *str3 = ft_strdup("Liste 3");

	ft_lstadd_front(&list, ft_lstnew(str1));
	ft_lstadd_front(&list, ft_lstnew(str2));
	ft_lstadd_front(&list, ft_lstnew(str3));

	t_list *temp = list;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}

	ft_lstclear(&list, del_content);
	return (0);
}*/