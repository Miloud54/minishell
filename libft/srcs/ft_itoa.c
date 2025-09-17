/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:22:37 by edidier           #+#    #+#             */
/*   Updated: 2025/07/16 13:26:15 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/*#include <stdio.h>

int	main(void)
{
	int		num;
	char	*str;

	num = 42;
	str = ft_itoa(num);
	printf("entier : %d\nchaîne : %s\n", num, str);
	free(str);
	num = -42;
	str = ft_itoa(num);
	printf("entier : %d\nchaîne : %s\n", num, str);
	free(str);
	return (0);
}*/
