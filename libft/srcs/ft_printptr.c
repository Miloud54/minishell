/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:40:08 by edidier           #+#    #+#             */
/*   Updated: 2025/07/21 18:49:18 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_ptr(uintptr_t nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (nb >= 16)
		count += ft_puthex_ptr(nb / 16);
	count += ft_putchar_count(base[nb % 16]);
	return (count);
}

int	ft_printptr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (count += ft_putstr_count("(nil)"));
	count += ft_putstr_count("0x");
	count += ft_puthex_ptr((uintptr_t)ptr);
	return (count);
}
