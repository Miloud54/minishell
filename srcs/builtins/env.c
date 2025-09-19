/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:42:54 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/18 19:41:45 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                             ENV - Explanation                              */
/* ************************************************************************** */

/* The 'env' command's purpose is to print all environnement variables available
in the shell. Each variable is printed on one line, as below :
KEY=value

Example:
$> env
PATH=/usr/bin:/bin
HOME=/home/user
SHELL=/bin/bash
... 

The minishell version of the 'env' command doesn't require to manage arguments*/

/* ************************************************************************** */
/*                               ENV - Function                               */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		printf("%s", envp[i]);
		printf("\n");
		i++;
	}
}

/* ************************************************************************** */
/*                             ENV - Main to test                             */
/* ************************************************************************** */

int		main(void)
{
	ft_env();
	return (0);
}