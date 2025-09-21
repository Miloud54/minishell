/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/21 18:34:31 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	validate_args(int ac)
{
	if (ac != 1)
	{
		write(STDERR_FILENO, "Error: minishell takes no arguments\n", 36);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (validate_args(ac))
		return (1);
	init_data(&data, envp);
	init_signals();
}

/*The main function should :
- initialize the variables data and token_list
- return 1 if init fails
- start main_loop
- clear everything (history, token_list and data)
- leave with the last exit code*/

// int		main(int ac, char **av, char **envp)
// {
// 	char	*line;

// 	(void)ac;
// 	(void)av;
// 	(void)envp;

// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*line == '\0')
// 		{
// 			free(line);
// 			continue;
// 		}
// 		add_history(line);
// 		if (ft_strcmp(line, "exit") == 0)
// 		{
// 			free(line);
// 			printf("exit\n");
// 			break;
// 		}
// 		//Debut du test de tokenization
// 		printf("Vous avez tape: %s\n", line);
// 		t_token	*tokens = tokenize(line);
// 		if (tokens)
// 		{
// 			print_tokens(tokens);
// 			free_tokens(&tokens);
// 		}
// 		else
// 			printf("Erreur: impossible de tokenizer la ligne.\n");
// 		//Fin du test de tokenization
// 		free(line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }
