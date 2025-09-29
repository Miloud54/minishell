/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:43:29 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/29 22:13:12 by emiliedidie      ###   ########.fr       */
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

static void	expand_cmd_args(t_cmd *cmd, t_data *data)
{
	int	i;
	char	*tmp;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = expand_variables(cmd->args[i], data);
		if (tmp != cmd->args[i])
			free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
}

static void	process_input(t_data *data, char *input)
{
    t_token	*tokens;
    t_cmd	**cmds;
    int		cmd_count;
    int		i;
    char	*expanded_input;

    if (!input || !*input)
        return ;
    if (ft_strcmp(input, "$?") == 0)
    {
        printf("%d\n", data->exit_status);
        return ;
    }
    expanded_input = expand_variables(input, data);
    if (!expanded_input)
        return ;
    tokens = lexer(expanded_input);
    free(expanded_input);
    if (!tokens)
        return ;
    cmds = parser(tokens, &cmd_count);
    if (cmds && cmd_count == 1 && cmds[0] && cmds[0]->args &&
        cmds[0]->args[0] && ft_strcmp(cmds[0]->args[0], "exit") == 0)
    {
        exec_builtin(data, cmds[0]);
        i = 0;
        while (i < cmd_count)
        {
            free_cmd(cmds[i]);
            i++;
        }
        free(cmds);
        free_tokens(tokens);
        exit(data->exit_status);
    }
    if (cmds && cmd_count > 0)
        execute_commands(cmds, cmd_count, data);
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
  return (data.exit_status);
}
