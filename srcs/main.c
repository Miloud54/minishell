/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/22 17:41:07 by edidier          ###   ########.fr       */
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

static int	handle_signal_state(t_data *data, char *input)
{
	if (g_signal_status != SIGINT)
		return (1);
	data->exit_status = 130;
	data->prompt_displayed = 1;
	g_signal_status = 0;
	if (*input == '\0')
	{
		free(input);
		return (0);
	}
	return (1);
}

static void	process_line(t_data *data, char *input)
{
	if (*input)
		add_history(input);
	process_input(data, input);
	if (*input)
		data->line_number++;
	free(input);
}

static void	main_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = next_input(data);
		if (!input)
			break ;
		if (!handle_signal_state(data, input))
			continue ;
		process_line(data, input);
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
