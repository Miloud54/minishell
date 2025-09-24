/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:47:43 by edidier           #+#    #+#             */
/*   Updated: 2025/09/24 15:51:17 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction a etendre aux autres builtins lorsque l'on voudra les executer

int	is_builtin_command(const char *input, char *builtin_name):
- qui vérifie si l’entrée correspond à n’importe quel builtin (exit, cd, echo,
	etc.)
- ensuite, on pourra dispatcher vers la bonne fonction builtin selon le 
	nom détecté et les arguments
*/

int	is_exit_command(const char *input)
{
	int	i;

	i = 0;
	skip_spaces(input, &i);
	if (ft_strncmp(input + i, "exit", 4) == 0 && (input[i + 4] == '\0'
			|| input[i + 4] == ' ' || (input[i + 4] >= 9 && input[i
				+ 4] <= 13)))
		return (1);
	return (0);
}
