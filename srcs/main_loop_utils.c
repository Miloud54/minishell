/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:02:12 by edidier           #+#    #+#             */
/*   Updated: 2025/10/22 18:02:12 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*readline_with_prompt(t_data *data)
{
	const char	*prompt;

	if (data->prompt_displayed)
	{
		prompt = "";
		data->prompt_displayed = 0;
	}
	else
		prompt = PROMPT;
	return (readline(prompt));
}

char	*next_input(t_data *data)
{
	char	*input;

	input = readline_with_prompt(data);
	if (!input)
	{
		if (g_signal_status == SIGINT)
		{
			data->exit_status = 130;
			g_signal_status = 0;
		}
		printf("exit\n");
	}
	return (input);
}
