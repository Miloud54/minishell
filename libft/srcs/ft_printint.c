/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:20:47 by edidier           #+#    #+#             */
/*   Updated: 2025/07/21 18:49:18 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printint(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	if (nb < 0)
	{
		count += ft_putchar_count('-');
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_printint(nb / 10);
	count += ft_putchar_count((nb % 10) + '0');
	return (count);
}
