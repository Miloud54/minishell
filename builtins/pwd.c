/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:00:17 by edidier           #+#    #+#             */
/*   Updated: 2025/09/18 17:14:20 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * pwd
 * ----
 * Affiche le répertoire courant sur stdout et un '\n'.
 * - Si des arguments sont fournis, on échoue ("too many arguments") comme bash.
 * - Implémentation : getcwd(NULL, 0) (GNU) => alloue dynamiquement.
 *   Si indisponible dans votre environnement, fallback: buffer PATH_MAX.
 * - En cas d'erreur getcwd: perror("pwd"), return 1.
 * - Succès: return 0.
 */
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_pwd(char **argv)
{
	char	*cwd;

	if (argv && argv[1])
	{
		perror("pwd: too many arguments");
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

