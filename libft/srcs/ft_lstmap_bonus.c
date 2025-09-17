/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:35:41 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:26:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	tmp->next = NULL;
	return (new);
}
/*
#include <stdio.h>

void	*f(void *content)
{
	return (strdup((char *)content));
}

void	del(void *content)
{
	free(content);
}
int	main(void)
{
	t_list	*element1;
	t_list	*element2;
	t_list	*list;
	t_list	*mapped;

	element1 = ft_lstnew(strdup("coucou"));
	element2 = ft_lstnew(strdup("ca va"));
	element1->next = element2;
	list = element1;
	mapped = ft_lstmap(list, f, del);
	while (mapped)
	{
		printf("%s\n", (char *)mapped->content);
		mapped = mapped->next;
	}
	return (0);
}*/
