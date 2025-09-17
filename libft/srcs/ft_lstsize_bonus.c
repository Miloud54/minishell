/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:26:17 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 14:02:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
/*#include <stdio.h>

int	main(void)
{
	t_list *head = NULL;

	head = ft_lstnew(ft_strdup("o"));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("t")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("q")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("b")));
	printf("%d\n", ft_lstsize(head));
	ft_lstclear(&head, free);
	return (0);
}*/
