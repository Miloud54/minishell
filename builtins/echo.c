/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:51:50 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/18 18:32:51 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                            ECHO - Explanation                              */
/* ************************************************************************** */

/*The echo command prints on the standard output (stdout) what we've given it as
an argument.

Example: 
$> echo hello world
$> hello world
$> echo hello world | cat -e
$> hello world$

The echo command only has one flag to manage in minishell: -n.
If the flag -n is present, echo does not print the final \n.

Example:
$> echo -n hello world
$> hello world%
$> echo -n hello world | cat -e
$> hello world%
*/

/* ************************************************************************** */
/*                               ECHO - Function                              */
/* ************************************************************************** */

#include <stdio.h> // for printf()
#include <unistd.h> // for write()
#include <stdbool.h> // for booleans
#include "../libft/inc/libft.h" // for ft_strcmp() for 2nd version of ft_echo

/*The function is_n_option takes an argument of the echo command as a string and
returns a boolean ; either the argument is a valid option (e.g. '-n' or '-nnnn')
or an invalid option (e.g. 'n', '-a' or '-nnnnna').*/

bool	is_n_option(char *av)
{
	int		i;

	i = 1;
	if (!av || av[0] != '-' || av[1] == '\0')
		return (false);
	while (av[i])
	{
		if (av[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(char **command)
{
	int		i;
	bool	need_newline;

	i = 0;
	need_newline = true;
	if (!command[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (command[i] != NULL && is_n_option(command[i]) == true)
	{
		need_newline = false;
		i++;
	}
	while (command[i] != NULL)
	{
		printf("%s", command[i]);
		if (command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (need_newline == true)
		printf("\n");
}

/* ************************************************************************** */
/*                     ECHO - Main to test both functions                     */
/* ************************************************************************** */

/*Main to test the 'is_n_option' function: */
// int		main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("%d", is_n_option(av[1]));
//	return (0);
// }

/*Main to test the 'ft_echo' short function (not commented, with i = 0): 
(the tests have to be executed 1 by 1 to see actual \n (% or $) with cat -e*/

// int		main(void)
// {
	// char	*test1[] = {"-n", "-nn", "hello", "world", "-n", NULL};
	// char	*test2[] = {NULL};
	// char	*test3[] = {"hello", "-n", "world", NULL};
	// char	*test4[] = {"-nnnn", "-n", "hello", "-n", NULL};
	// char	*test5[] = {"-n", NULL};
	// char	*test6[] = {"hello", "-n", NULL};
	// char	*test7[] = {"-na", "hello", NULL};

	// ft_echo(test7);
	// return (0);
// }

/* ************************************************************************** */
/*                 ECHO - 2nd version, longer, with ft_strcmp                 */
/* ************************************************************************** */

/*Long version of ft_echo that can take as av[0] either echo or the next av:*/

// void	ft_echo(char **command)
// {
// 	int		i;
// 	bool	need_newline;
// 	bool	printed = false;

// 	if (command[0] && ft_strcmp(command[0], "echo") == 0)
// 		i = 1;
// 	else
// 		i = 0;
// 	need_newline = true;
// 	if (!command[i])
// 	{
// 		write(1, "\n", 1);
// 		return ;
// 	}
// 	while (command[i] != NULL && is_n_option(command[i]) == true)
// 	{
// 		need_newline = false;
// 		i++;
// 	}
// 	int j = i;
// 	while (command[j] != NULL)
// 	{
// 		printf("%s", command[j]);
// 		printed = true;
// 		if (command[j + 1] != NULL)
// 			printf(" ");
// 		j++;
// 	}
// 	if (need_newline == true && printed)
// 		printf("\n");
// }

/*Main to test the 'ft_echo' long function: 
(the tests have to be executed 1 by 1 to see actual \n (% or $) with cat -e*/
// int		main(void)
// {
	// char	*test1[] = {"echo", "-n", "-nn", "hello", "world", "-n", NULL};
	// char	*test2[] = {"echo", NULL};
	// char	*test3[] = {"echo", "hello", "-n", "world", NULL};
	// char	*test4[] = {"echo", "-nnnn", "-n", "hello", "-n", NULL};
	// char	*test5[] = {"echo", "-n", NULL};
	// char	*test6[] = {"echo", "hello", "-n", NULL};
	// char	*test7[] = {"echo", "-na", "hello", NULL};

	// 	ft_echo(test7);
	// 	return (0);
// }