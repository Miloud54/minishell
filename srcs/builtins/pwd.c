/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:17 by edidier           #+#    #+#             */
/*   Updated: 2025/09/23 15:46:14 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * pwd:
 * Prints the current working directory to stdout followed by a newline
 * Uses getcwd(NULL, 0) for dynamic allocation (GNU extension)
 */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	*cwd;

	if (argv && argv[1])
	{
		write(2, "pwd: too many arguments\n", 24);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
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
