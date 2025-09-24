/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:00:00 by edidier           #+#    #+#             */
/*   Updated: 2025/09/24 12:03:45 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	digit;

	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (overflow((long long)(res->result), digit, sign))
		{
			res->overflow = 1;
			return (0);
		}
		res->result = (res->result) * 10 + digit;
		(*i)++;
	}
	return (1);
}

void	exit_numeric_error(t_data *data, char *arg)
{
	write(1, "exit\n", 5);
	ft_putstr_fd("minishell: exit ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_data(data);
	exit(2);
}
