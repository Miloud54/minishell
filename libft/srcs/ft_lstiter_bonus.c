/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:32:32 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:59:21 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*#include <stdio.h>

void	print_uppercase(void *content)
{
	char	*str;

	str = (char *)content;
	while (*str)
	{
		putchar(ft_toupper(*str));
		str++;
	}
	putchar('\n');
}
int	main(void)
{
	t_list *n1 = ft_lstnew(ft_strdup("yo"));
	t_list *n2 = ft_lstnew(ft_strdup("ca"));
	t_list *n3 = ft_lstnew(ft_strdup("va"));

	if (!n1 || !n2 || !n3)
		return (1);
	ft_lstadd_back(&n1, n2);
	ft_lstadd_back(&n1, n3);
	ft_lstiter(n1, print_uppercase);
	ft_lstclear(&n1, free);
	return (0);
}*/