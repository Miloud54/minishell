/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:20 by edidier           #+#    #+#             */
/*   Updated: 2025/09/18 17:31:19 by edidier          ###   ########.fr       */
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
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long	ft_atol(const char *str, int *error)
{
	size_t	i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	*error = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		*error = 1;
	return (result * sign);
}

int	ft_exit(int argc, char **argv, int last_status)
{
	int		error;
	long	val;

	if (argc == 1)
	{
		write(1, "exit\n", 5);
		exit(last_status);
	}
	if (argc == 2)
	{
		val = ft_atol(argv[1], &error);
		if (error)
		{
			ft_putstr_fd("minishel: exit ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			write(1, "exit\n", 5);
			exit(2);
		}
		else
		{
			write(1, "exit\n", 5);
			exit((unsigned char)val);
		}
	}
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
}
