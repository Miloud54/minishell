/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:59:21 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:59:31 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	store_escape_char(t_quote_context *context, char next)
{
	if (context->result)
		context->result[context->len] = next;
	context->len++;
	context->index += 2;
	return (1);
}

int	handle_escape(char *str, t_quote_context *context)
{
	char	next;

	if (str[context->index] != '\\' || context->state.in_single)
		return (0);
	next = str[context->index + 1];
	if (!next)
	{
		context->index++;
		return (1);
	}
	if (!context->state.in_double)
		return (store_escape_char(context, next));
	if (next == '\n')
	{
		context->index += 2;
		return (1);
	}
	if (!ft_strchr("\"$\\`", next))
		return (0);
	return (store_escape_char(context, next));
}

int	handle_quote_toggle(char c, t_quote_context *context)
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
