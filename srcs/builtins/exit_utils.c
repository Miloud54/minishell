/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:00:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/06 12:14:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	overflow(long long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > (LLONG_MAX - digit) / 10)
			return (1);
	}
	else
	{
		if (result < (LLONG_MIN - digit) / 10)
			return (1);
	}
	return (0);
}

int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[(*i)++] == '-')
			sign = -1;
	}
	return (sign);
}

int	parse_digits(const char *str, int *i, int sign, t_parse_result *res)
{
	unsigned long long	acc;
	unsigned long long	limit;
	int					digit;

	acc = 0ULL;
	if (sign == 1)
		limit = (unsigned long long)LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (acc > limit / 10ULL || (acc == limit / 10ULL
				&& (unsigned long long)digit > (limit % 10ULL)))
		{
			res->overflow = 1;
			return (0);
		}
		acc = acc * 10ULL + (unsigned long long)digit;
		(*i)++;
	}
	res->result = (long long)acc;
	return (1);
}

void	skip_spaces(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}
