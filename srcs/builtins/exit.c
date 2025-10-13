/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:20 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 21:11:08 by bde-la-p         ###   ########.fr       */
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

int	ft_atol(const char *str, int *overflow_flag)
{
	t_parse_result	res;
	int				i;
	int				sign;

	if (!str)
		return (0);
	i = 0;
	res.result = 0;
	res.overflow = 0;
	skip_spaces(str, &i);
	sign = parse_sign(str, &i);
	if (!parse_digits(str, &i, sign, &res))
	{
		*overflow_flag = 1;
		return (0);
	}
	skip_spaces(str, &i);
	if (str[i] != '\0')
		res.overflow = 1;
	*overflow_flag = res.overflow;
	return ((int)((res.result * sign) % 256));
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
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	skip_spaces(str, &i);
	return (str[i] == '\0');
}

void	exit_numeric_error(t_data *data, char *arg)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_data(data);
	exit(2);
}

static int	handle_exit_args(t_data *data, char **argv)
{
	int		error;
	long	val;

	error = 0;
	val = ft_atol(argv[1], &error);
	if (!is_valid_number(argv[1]) || error)
		exit_numeric_error(data, argv[1]);
	if (argv[1] && argv[2])
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		data->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	free_data(data);
	exit((unsigned char)val);
	return (0);
}

int	ft_exit(t_data *data, char **argv)
{
	if (!argv[1])
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		free_data(data);
		exit(data->exit_status);
	}
	return (handle_exit_args(data, argv));
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
