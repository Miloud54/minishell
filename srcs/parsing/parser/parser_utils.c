/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:10:00 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/10 15:12:17 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_redir_token(t_token *token)
{
	return (token->type >= TOKEN_REDIR_IN
		&& token->type <= TOKEN_REDIR_HEREDOC);
}

int	is_cd_token(t_token *start)
{
	return (start && start->type == TOKEN_WORD && start->value
		&& ft_strcmp(start->value, "cd") == 0);
}

int	add_arg_to_cmd(t_cmd *cmd, t_token *current, int arg_index)
{
	cmd->args[arg_index] = ft_strdup(current->value);
	if (!cmd->args[arg_index])
		return (-1);
	return (0);
}

void	skip_redirect_tokens(t_token **current, t_token *end)
{
	*current = (*current)->next;
	if (*current && *current != end && (*current)->type == TOKEN_WORD)
		*current = (*current)->next;
}
