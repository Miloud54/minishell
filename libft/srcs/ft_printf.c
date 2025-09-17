/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:28:29 by edidier           #+#    #+#             */
/*   Updated: 2025/07/21 18:49:54 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printhex(unsigned int nb, char format)
{
	if (format == 'x')
		return (ft_printhexlow(nb));
	return (ft_printhexup(nb));
}

static int	ft_check_format(const char format, va_list args)
{
	if (format == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_printstring(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_printptr(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (ft_printint(va_arg(args, int)));
	else if (format == 'u')
		return (ft_printunsigned(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_printhex(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_printchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_check_format(format[i + 1], args);
			i++;
		}
		else
			count += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

/*#include <stdio.h>

int	main(void)
{
	int	val;
	int	ret;

	val = 42;
	printf("Tests classiques\n");
	printf("%c\n", 'E');
	ft_printf("%c\n", 'E');
	printf("%s\n", "yooooo");
	ft_printf("%s\n", "yooooo");
	printf("%p\n", &val);
	ft_printf("%p\n", &val);
	printf("%p\n", NULL);
	ft_printf("%p\n", NULL);
	printf("%d %i\n", 642, -642);
	ft_printf("%d %i\n", 642, -642);
	// printf("%d\n", -2147483648);
	ft_printf("%d\n", -2147483648);
	printf("%d\n", 2147483647);
	ft_printf("%d\n", 2147483647);
	printf("%u\n", 4294967295U);
	ft_printf("%u\n", 4294967295U);
	printf("%x | %X\n", 4556, 4556);
	ft_printf("%x | %X\n", 4556, 4556);
	printf("%%\n");
	ft_printf("%%\n");
	// printf("%\n");
	ft_printf("% \n");
	printf("Test string vide\n");
	printf("%s\n", "");
	ft_printf("%s\n", "");
	printf("Test avec 0\n");
	printf("%d\n", 0);
	ft_printf("%d\n", 0);
	printf("%u\n", 0);
	ft_printf("%u\n", 0);
	printf("%x | %X\n", 0, 0);
	ft_printf("%x | %X\n", 0, 0);
	printf("Test combi multiples\n");
	printf("%c | %s | %d | %x | %X\n", 'T', "wesh", 42, 42, 42);
	ft_printf("%c | %s | %d | %x | %X\n", 'T', "wesh", 42, 42, 42);
	printf("Test conversions consecutives\n");
	printf("%d%d%d\n", 42, 43, 44);
	ft_printf("%d%d%d\n", 42, 43, 44);
	printf("%c%c%c\n", 'e', 'm', 'i');
	ft_printf("%c%c%c\n", 'e', 'm', 'i');
	printf("Test retour valeur\n");
	ret = printf("Coucou %s\n", "ca va");
	printf("%d\n", ret);
	ret = ft_printf("Coucou %s\n", "ca va");
	ft_printf("%d\n", ret);
	ret = printf("");
	printf("%d\n", ret);
	ret = ft_printf("");
	ft_printf("%d\n", ret);
	ret = printf("%%");
	printf("%d\n", ret);
	ret = ft_printf("%%");
	ft_printf("%d\n", ret);
	printf("Tests\n");
	printf("%% %% %%\n");
	ft_printf("%% %% %%\n");
	// printf("%q\n");
	ft_printf("%q\n");
	printf("%d\n", printf("ptdr\n"));
	ft_printf("%d\n", ft_printf("ptdr\n"));
}
int	main(void)
{
	int	val;
	char *ptr = NULL;

	val = printf(ptr);
	printf("%d\n", val);
	val = ft_printf(ptr);
	ft_printf("%d\n", val);
}
int	main(void)
{
	char str[1204];

	memset(str, 'E', 1203);
	str[1203] = '\0';
	printf("%s\n\n", str);
	ft_printf("%s\n", str);
}

int	main(void)
{
	int	val;

	val = printf(0);
	printf("%d\n", val);
	val = ft_printf(0);
	ft_printf("%d\n", val);
}*/
