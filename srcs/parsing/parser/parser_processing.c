/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:35:00 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 16:35:52 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Processes a single redirection token */
static int	process_redirect_token(t_cmd *cmd, t_token **current,
		int *redir_idx)
{
	if (*redir_idx >= cmd->redirect_count)
		return (-1);
	cmd->redirects[*redir_idx].type = (*current)->type;
	*current = (*current)->next;
	if (!*current || (*current)->type != TOKEN_WORD)
		return (-1);
	cmd->redirects[*redir_idx].file = remove_quotes((*current)->value);
	if (!cmd->redirects[*redir_idx].file)
		return (-1);
	cmd->redirects[*redir_idx].heredoc_fd = -1;
	(*redir_idx)++;
	return (0);
}

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
