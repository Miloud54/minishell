/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:20 by edidier           #+#    #+#             */
/*   Updated: 2025/09/19 15:34:57 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * builtin: exit
 * Usage: exit [n]
 * Comportement :
 *  - Sans argument  : quitte avec le dernier statut (ms->last_status).
 *  - Avec <n> entier: quitte avec (unsigned char)n.
 *  - <n> non numérique/overflow : affiche
 *      "minishell: exit: <arg>: numeric argument required" et quitte avec 2.
 *  - Trop d'arguments : affiche
 *      "minishell: exit: too many arguments", NE QUITTE PAS, retourne 1.
 * Affichage :
 *
	- Imprimer "exit\n" uniquement si on quitte réellement dans le parent interactif
 *    (pas dans un enfant/pipeline).
 * Notes :
 *  - Parser avec strtoll + contrôle endptr/ERANGE ; erreurs sur stderr.
 */

#include "minishell.h"

int overflow(long long result, int digit, int sign)
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

int ft_atol(const char *str, int *overflow_flag)
{
	unsigned long long result;
	int i;
	int sign;
	int digit;

	if (!str)
		return (0);
	i = 0;
	result = 0;
	sign = 1;
	*overflow_flag = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (overflow((long long)result, digit, sign))
			return (*overflow_flag = 1, 0);
		result = result * 10 + digit;
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		*overflow_flag = 1;
	return ((int)((result * sign) % 256));
	
}

int is_valid_number(char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
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
			while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			break;
		}
		else 
			return (0);
	}
	if (str[i] == '\0')
		return (1);
	else 
		return (0);
}

int should_print_exit(void)
{
	return (isatty(STDIN_FILENO));
}

int	ft_exit(char **argv, int last_status)
{
	int		error;
	long	val;

	if (!argv[1])
	{
		if (should_print_exit())
			write(1, "exit\n", 5);
		exit(last_status);
	}	
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_valid_number(argv[1]))
	{
		if (should_print_exit())
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		write(1, "exit\n", 5);
		exit(2);
	}
	val = ft_atol(argv[1], &errno);
	if (errno)
	{
		if (should_print_exit())
			write(1, "exit\n", 5);
		ft_putstr_fd("minishell: exit ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		write(1, "exit\n", 5);
		exit(2);
	}
	if (should_print_exit())
		write(1, "exit\n", 5);
	exit (val);
	return (0);
}

int	main(void)
{
	char	*argv1[] = {"exit", "1", "2", NULL};
	int		result1;
	char	*argv2[] = {"exit", "abc", NULL};

	printf("Test 1: exit avec trop d'arguments\n");
	result1 = ft_exit(argv1, 4);
	printf("Code de retour: %d\n\n", result1);
	
	printf("Test 2: exit avec argument invalide - va quitter!\n");
	ft_exit(argv2, 42);
	
	printf("Cette ligne ne devrait pas s'afficher\n");
	return (0);
}