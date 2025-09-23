/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:20 by edidier           #+#    #+#             */
/*   Updated: 2025/09/23 16:04:55 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * exit
 * Usage: exit [n]
 * Behavior:
 *  - No argument: exits with data->exit_status
 *  - With <n> as integer: exits with (unsigned char)n
 *  - Always prints "exit\n" before exiting
 */

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

static int	parse_sign_digits(const char *str, int *i,
		unsigned long long *result, int *sign, int *overflow_flag)
{
	int	digit;

	*sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			*sign = -1;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (overflow((long long)(*result), digit, *sign))
		{
			*overflow_flag = 1;
			return (0);
		}
		*result = (*result) * 10 + digit;
		(*i)++;
	}
	return (1);
}

int	ft_atol(const char *str, int *overflow_flag)
{
	unsigned long long	result;
	int					i;
	int					sign;

	if (!str)
		return (0);
	i = 0;
	result = 0;
	*overflow_flag = 0;
	skip_spaces(str, &i);
	if (!parse_sign_digits(str, &i, &result, &sign, overflow_flag))
		return (0);
	skip_spaces(str, &i);
	if (str[i] != '\0')
		*overflow_flag = 1;
	return ((int)((result * sign) % 256));
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		{
			skip_spaces(str, &i);
			break ;
		}
		else
			return (0);
	}
	return (str[i] == '\0');
}

int	ft_exit(t_data *data, char **argv)
{
	int		error;
	long	val;

	if (!argv[1])
	{
		write(1, "exit\n", 5);
		free_data(data);
		exit(data->exit_status);
	}
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	val = ft_atol(argv[1], &error);
	if (!is_valid_number(argv[1]) || error)
	{
		write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_data(data);
		exit(2);
	}
	write(1, "exit\n", 5);
	free_data(data);
	exit((unsigned char)val);
	return (0);
}

// int	main(void)
// {
// 	char	*argv1[] = {"exit", "1", "2", NULL};
// 	int		result1;
// 	char	*argv2[] = {"exit", "abc", NULL};

// 	printf("Test 1: exit avec trop d'arguments\n");
// 	result1 = ft_exit(argv1, 4);
// 	printf("Code de retour: %d\n\n", result1);

// 	printf("Test 2: exit avec argument invalide - va quitter!\n");
// 	ft_exit(argv2, 42);

// 	printf("Cette ligne ne devrait pas s'afficher\n");
// 	return (0);
// }