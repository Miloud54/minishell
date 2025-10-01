/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/01 14:05:13 by edidier          ###   ########.fr       */
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
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
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
	free_data(&data);
	return (data.exit_status);
}
