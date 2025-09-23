/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:51:50 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/23 16:04:06 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                            ECHO - Explanation                              */
/* ************************************************************************** */

/*The echo cmd prints on the standard output (stdout) what we've given it as
an argument.

Example: 
$> echo hello world
$> hello world
$> echo hello world | cat -e
$> hello world$

The echo cmd only has one flag to manage in minishell: -n.
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

#include "minishell.h" // for ft_strcmp() for 2nd version of ft_echo

/*The function is_n_option takes an argument of the echo cmd as a string and
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

void	ft_echo(t_cmd *cmd, t_data *data)
{
	int		i;
	bool	need_newline;

	i = 0;
	need_newline = true;
	if (!cmd->args[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (cmd->args[i] != NULL && is_n_option(cmd->args[i]) == true)
	{
		need_newline = false;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (need_newline == true)
		printf("\n");
	data->exit_status = 0;
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

// void	ft_echo(char **cmd)
// {
// 	int		i;
// 	bool	need_newline;
// 	bool	printed = false;

// 	if (cmd[0] && ft_strcmp(cmd[0], "echo") == 0)
// 		i = 1;
// 	else
// 		i = 0;
// 	need_newline = true;
// 	if (!cmd[i])
// 	{
// 		write(1, "\n", 1);
// 		return ;
// 	}
// 	while (cmd[i] != NULL && is_n_option(cmd[i]) == true)
// 	{
// 		need_newline = false;
// 		i++;
// 	}
// 	int j = i;
// 	while (cmd[j] != NULL)
// 	{
// 		printf("%s", cmd[j]);
// 		printed = true;
// 		if (cmd[j + 1] != NULL)
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