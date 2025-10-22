/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:39:28 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:50:55 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Validates input and initializes parsing */

static t_cmd	**init_parser(t_token *tokens, int *cmd_count)
{
	t_cmd	**commands;

	if (!tokens || !cmd_count)
		return (NULL);
	if (!validate_token_sequence(tokens))
		return (NULL);
	*cmd_count = count_commands(tokens);
	if (*cmd_count <= 0)
		return (NULL);
	commands = malloc(sizeof(t_cmd *) * *cmd_count);
	return (commands);
}

/* Processes all commands in the token sequence */

static int	process_all_commands(t_cmd **commands, t_token *tokens,
		int cmd_count)
{
	t_token	*current;
	t_token	*next_pipe;
	int		i;

	current = tokens;
	i = 0;
	while (current && i < cmd_count)
	{
		next_pipe = find_next_pipe(current);
		commands[i] = parse_single_cmd(current, next_pipe);
		if (!commands[i])
		{
			cleanup_commands_on_error(commands, i);
			return (-1);
		}
		if (next_pipe)
			current = next_pipe->next;
		else
			current = NULL;
		i++;
	}
	return (0);
}

/*Main entry point for parsing; initializes the parser, processes all commands,
and returns the array of parsed command structures (or NULL on error)*/

t_cmd	**parser(t_token *tokens, int *cmd_count)
{
	t_cmd	**commands;

	commands = init_parser(tokens, cmd_count);
	if (!commands)
		return (NULL);
	if (process_all_commands(commands, tokens, *cmd_count) == -1)
		return (NULL);
	return (commands);
}

/*These functions coordinate the overall parsing process, from validation and
memory allocation to splitting and parsing each command in the input*/