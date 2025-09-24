/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/24 18:51:17 by bde-la-p         ###   ########.fr       */
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
	t_cmd	**cmds;
	int		cmd_count;
	int		i;

	if (!input || !*input)
		return ;
	tokens = lexer(input);
	if (!tokens)
		return ;
	cmds = parser(tokens, &cmd_count);
	if (cmds && cmds[0] && cmds[0]->args && is_builtin(cmds[0]->args[0]))
		exec_builtin(data, cmds[0]);
	else
	{
		// Here goes the execution of external commands (fork/exec)
	}
	if (cmds)
	{
		i = 0;
		while (i < cmd_count)
		{
			free_cmd(cmds[i]);
			i++;
		}
		free(cmds);
	}
	free_tokens(tokens);
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
}

