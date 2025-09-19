/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/19 15:50:28 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*The main function should :
- initialize the variables data and token_list
- return 1 if init fails
- start main_loop
- clear everything (history, token_list and data)
- leave with the last exit code*/



int		main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)envp;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			printf("exit\n");
			break;
		}
		printf("Vous avez tape: %s\n", line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
