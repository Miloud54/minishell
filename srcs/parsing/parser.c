/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:39:28 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 16:13:37 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_commands(t_token *tokens)
{
	int count;
	t_token *current;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static int count_args_in_cmd(t_token *start, t_token *end)
{
	int count;
	t_token *current;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type == TOKEN_WORD)m
			count++;
		else if (current->type != TOKEN_PIPE)
		{
			current = current->next;
			if (current && current != end)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	return (count);
}

static count_redirect_in_cmd(t_token *start, t_token *end)
{
	int count;
	t_token *current;

	count = 0;
	current = start;
	while (current && current != end)
	{
		if (current->type != TOKEN_WORD && current->type != TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static t_token *find_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	return (tokens);
}

static int parse_redirects(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token *current;
	int redir_index;

	current = start;
	redir_index = 0;
	while (current && current != end)
	{
		if (current->type != TOKEN_WORD && current->type != TOKEN_PIPE)
		{
			cmd->redirects[redir_index].type = current->type;
			current = current->next;
			if (current && current != end && current->type == TOKEN_WORD)
			{
				cmd->redirects[redir_index].file = remove_quotes(current->value);
				cmd->redirects[redir_index].heredoc_fd = -1;
				redir_index++;
			}
			else 
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int parse_args(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token *current;
	int arg_index;

	current = start;
	arg_index = 0;
	while (current && current != end)
	{
		if (current->type == TOKEN_WORD)
		{
			cmd->args[arg_index] = remove_quotes(current->value);
			if (!cmd->args[arg_index])
				return (-1);
			arg_index++;
		}
		else if (current->type != TOKEN_PIPE)
		{
			current = current->next;
			if (current && current != end)
				current = current-next;
			continue ;
		}
		current = current->next;
	}
	cmd->args[arg_index] = NULL;
	return (0);
}

static t_cmd *parse_single_cmd(t_token *start, t_token *end)
{
	t_cmd *cmd;
	int arg_count;
	int redir_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	arg_count = count_args_in_cmd(start, end);
	redir_count = count_redirect_in_cmd(start, end);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{m
		free(cmd);
		return (NULL);
	}
	if (redir_count > 0)
	{
		cmd->redirects = malloc(sizeof(t_redirect) * redir_count);
		if (!cmd->redirects)
		{
			free(cmd->args);
			free(cmd);
			return (NULL);
		}
	}
	else
		cmd->redirects = NULL;
	if (parse_args(cmd, start, end) == -1 || parse_redirects(cmd, start, end) == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd **parser(t_token *tokens, int *cmd_count)
{
	t_cmd **commands;
	t_token *current;
	t_token *next_pipe;
	int i;

	if (!tokens)
		return (NULL);
	*cmd_count = count_commands(tokens);
	commands = malloc(sizeof(t_cmd*) * *cmd_count);
	if (!commands)
		return (NULL);
	current = tokens;
	i = 0;
	while (current && i < *cmd_count)
	{
		next_pipe = find_next_pipe(current);
		commands[i] = parse_single_cmd(current, next_pipe);
		if (!commands[i])
		{
			while (--i >= 0)
				free_cmd(commands[i]);
			free(commands);
			return (NULL);
		}
		if (next_pipe)
			current = next_pipe->next;
		else	
			current = NULL;
		i++;
	}
	return (commands);
}

