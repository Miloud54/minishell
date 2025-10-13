/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:39:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:47:43 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_escape(char *str, t_quote_context *context)
{
	char	next;
	int		should_copy;

	if (str[context->index] != '\\' || context->state.in_single)
		return (0);
	next = str[context->index + 1];
	if (!next)
	{
		context->index++;
		return (1);
	}
	if (context->state.in_double && next == '\n')
	{
		context->index += 2;
		return (1);
	}
	should_copy = !context->state.in_double || ft_strchr("\"$\\`", next);
	if (!should_copy)
		return (0);
	if (context->result)
		context->result[context->len] = next;
	context->len++;
	context->index += 2;
	return (1);
}

static int	handle_quote_toggle(char c, t_quote_context *context)
{
	if (c == '\'' && !context->state.in_double)
	{
		context->state.in_single = !context->state.in_single;
		return (1);
	}
	if (c == '"' && !context->state.in_single)
	{
		context->state.in_double = !context->state.in_double;
		return (1);
	}
	return (0);
}

static int	process_without_quotes(char *str, char *result)
{
	t_quote_context	context;

	context.index = 0;
	context.len = 0;
	context.result = result;
	context.state.in_single = 0;
	context.state.in_double = 0;
	while (str[context.index])
	{
		if (handle_escape(str, &context))
			continue ;
		if (handle_quote_toggle(str[context.index], &context))
		{
			context.index++;
			continue ;
		}
		if (context.result)
			context.result[context.len] = str[context.index];
		context.len++;
		context.index++;
	}
	if (context.result)
		context.result[context.len] = '\0';
	return (context.len);
}

int	count_unquoted_len(char *str)
{
	return (process_without_quotes(str, NULL));
}

void	copy_without_quotes(char *str, char *result)
{
	process_without_quotes(str, result);
}
