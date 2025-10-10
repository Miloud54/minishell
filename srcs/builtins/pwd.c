/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:17 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 13:43:58 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * pwd:
 * Prints the current working directory to stdout followed by a newline
 * Uses getcwd(NULL, 0) for dynamic allocation (GNU extension)
 */

#include "minishell.h"

static int	check_options(char **argv)
{
	int	i;

	i = 1;
	if (argv && argv[1])
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			if (argv[i][1] == '-' || argv[i][2] == '-')
			{
				write(2, "pwd: --: ivalid option\npwd: usage: pwd [-LP]\n", 46);
				return (1);
			}
			write(2, "pwd: ", 5);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, ": invalid option\npwd: usage: pwd [-LP]\n", 39);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_pwd(char **argv)
{
	char	*cwd;

	if (check_options(argv))
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		write(2, "pwd: error retrieving current directory: getcwd: ", 49);
		write(2, "cannot access parent directories: No such file or ", 50);
		write(2, "directory\n", 10);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

/*int main()
{
	char *argv1[] = {"pwd", NULL};
	int result1 = pwd(argv1);
	printf("Code retour: %d\n\n", result1);

	char *argv2[] = {"pwd", "argument", NULL};
	int result2 = pwd(argv2);
	printf("Code retour: %d\n\n", result2);

	char *argv3[] = {"pwd", "arg1", "arg2", NULL};
	int result3 = pwd(argv3);
	printf("Code retour: %d\n\n", result3);

	return (0);
}*/
