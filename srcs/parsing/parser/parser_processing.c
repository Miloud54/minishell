/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:35:00 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 16:41:30 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_uses_quotes(char *value)
{
	int	i;

	if (!value)
		return (0);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\\' && value[i + 1])
		{
			i += 2;
			continue ;
		}
		if (value[i] == '\'' || value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/*Processes a single redirection token in the token list, sets its type and
file in the command structure, and initializes heredoc file descriptor*/

static int	process_redirect_token(t_cmd *cmd, t_token **current,
		int *redir_idx)
{
	int	quoted;

	if (*redir_idx >= cmd->redirect_count)
		return (-1);
	cmd->redirects[*redir_idx] = (t_redirect){0};
	cmd->redirects[*redir_idx].type = (*current)->type;
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
		return (-1);
	quoted = token_uses_quotes((*current)->value);
	cmd->redirects[*redir_idx].file = remove_quotes((*current)->value);
	if (!cmd->redirects[*redir_idx].file)
		return (-1);
	cmd->redirects[*redir_idx].heredoc_fd = -1;
	if (cmd->redirects[*redir_idx].type == TOKEN_REDIR_HEREDOC)
		cmd->redirects[*redir_idx].heredoc_quoted = quoted;
	else
		cmd->redirects[*redir_idx].heredoc_quoted = 0;
	(*redir_idx)++;
	return (0);
}

/*Iterates through the token list for a command,
	processes all redirection tokens
using process_redirect_token, and fills the command's redirection array*/

int	parse_redirects(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*current;
	int		redir_index;

	current = start;
	redir_index = 0;
	while (current && current != end)
	{
		if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_REDIR_HEREDOC)
		{
			if (process_redirect_token(cmd, &current, &redir_index) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

/*Parses a single command from a range of tokens. Allocates and initializes
the command structure, counts arguments and redirections, allocates memory,
and fills the command with its arguments and redirections*/

t_cmd	*parse_single_cmd(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	int		arg_count;
	int		redir_count;

	if (!start)
		return (NULL);
	cmd = create_new_cmd();
	if (!cmd)
		return (NULL);
	arg_count = count_args_in_cmd(start, end);
	redir_count = count_redirect_in_cmd(start, end);
	if (!allocate_cmd_memory(cmd, arg_count, redir_count))
	{
		free(cmd);
		return (NULL);
	}
	if (fill_cmd_content(cmd, start, end) == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

/*These functions handle the extraction and storage of redirection
information and the overall parsing of a single command from tokens*/
