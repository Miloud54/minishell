/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:39:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:59:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_without_quotes(char *str, char *result)
{
	t_quote_context	context;

	context = (t_quote_context){0, 0, result, {0, 0}};
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
