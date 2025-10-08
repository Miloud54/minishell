/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:50:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/08 12:33:18 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Skips redirection tokens and their files */

static void	skip_redirect_tokens(t_token **current, t_token *end)
{
	*current = (*current)->next;
	if (*current && *current != end && (*current)->type == TOKEN_WORD)
		*current = (*current)->next;
}

/*Fills the command's argument array (cmd->args) by iterating through tokens,
removing quotes from argument values,
	and skipping redirection tokens and their files*/

int	parse_args(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*current;
	int		arg_index;
	int		is_cd;

	current = start;
	arg_index = 0;
	is_cd = 0;
	if (start && start->type == TOKEN_WORD && start->value
		&& ft_strcmp(start->value, "cd") == 0)
		is_cd = 1;
	while (current && current != end)
	{
		if (current->type == TOKEN_WORD)
		{
			if (is_cd)
				cmd->args[arg_index] = ft_strdup(current->value);
			else
				cmd->args[arg_index] = ft_strdup(current->value);
			if (!cmd->args[arg_index])
				return (-1);
			arg_index++;
		}
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			skip_redirect_tokens(&current, end);
			continue ;
		}
		current = current->next;
	}
	cmd->args[arg_index] = NULL;
	return (0);
}

/* Creates and initializes a new command structure */

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_defaults(cmd);
	return (cmd);
}

/* Parses and fills a single command structure */

int	fill_cmd_content(t_cmd *cmd, t_token *start, t_token *end)
{
	if (parse_args(cmd, start, end) == -1)
		return (-1);
	if (parse_redirects(cmd, start, end) == -1)
		return (-1);
	return (0);
}

/* Cleans up allocated commands array on error */

void	cleanup_commands_on_error(t_cmd **commands, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (commands[i])
			free_cmd(commands[i]);
		i++;
	}
	free(commands);
}

/*These functions are used to parse command-line tokens into
structured command data, handling arguments and redirections*/