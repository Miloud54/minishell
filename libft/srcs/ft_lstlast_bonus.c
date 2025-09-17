/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:26:59 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:26:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*#include <stdio.h>

int	main(void)
{
	t_list *n1 = ft_lstnew(ft_strdup("coucou"));
	t_list *n2 = ft_lstnew(ft_strdup("ca"));
	t_list *n3 = ft_lstnew(ft_strdup("va"));
	t_list *last;

	if (!n1 || !n2 || !n3)
		return (1);
	ft_lstadd_back(&n1, n2);
	ft_lstadd_back(&n1, n3);
	last = ft_lstlast(n1);
	if (last && last->content)
		printf("%s\n", (char *)last->content);
	ft_lstclear(&n1, free);

	return (0);
}*/