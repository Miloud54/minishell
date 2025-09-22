/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/22 18:00:18 by bde-la-p         ###   ########.fr       */
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

static void	process_input(t_data *data, char *input)
{
	t_token	*tokens;
	t_cmd	**commands;
	char	*expanded_input;
	int		cmd_count;
	int		i;

	if (!input || !*input)
		return ;
	
	// Gestion de la commande exit // a degager qund le builtin sera fait.
	if (ft_strcmp(input, "exit") == 0)
	{
		printf("exit\n");
		exit(data->exit_status);
	}
	
	if (!validate_syntax(input))
	{
		data->exit_status = 2;
		return ;
	}
	expanded_input = expand_variables(input, data);
	if (!expanded_input)
		return ;
	tokens = lexer(expanded_input);
	if (!tokens)
	{
		free(expanded_input);
		return ;
	}
	commands = parser(tokens, &cmd_count);
	if (!commands)
	{
		free_tokens(tokens);
		free(expanded_input);
		return ;
	}
	
	//TODO : executer les commandes.
	i = 0;
	while (i < cmd_count)
	{
		free_cmd(commands[i]);
		i++;
	}
	free(commands);
	free_tokens(tokens);
	free(expanded_input);
}

static void	main_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		if (g_signal_status == SIGINT)
		{
			data->exit_status = 130;
			g_signal_status = 0;
		}
		input = readline(PROMPT);
		if (!input)  // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		if (*input)  // Si la ligne n'est pas vide
			add_history(input);
		
		// // Commande exit ??????
		// if (ft_strcmp(input, "exit") == 0)
		// {
		// 	free(input);
		// 	printf("exit\n");
		// 	break;
		// }
		
		process_input(data, input);
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (validate_args(ac))
		return (1);
	init_data(&data, envp);
	init_signals();
	main_loop(&data);
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
