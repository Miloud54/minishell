/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:35 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:48:51 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	handle_backslash_in_double(char *input, t_size_context *context)
{
	if (!context->state.in_double)
		return (0);
	if (input[context->index + 1] == '\n')
	{
		context->index += 2;
		return (1);
	}
	if (ft_strchr("\"$\\`", input[context->index + 1]))
	{
		context->size++;
		context->index += 2;
		return (1);
	}
	context->size++;
	context->index++;
	return (1);
}

static int	handle_backslash_size(char *input, t_size_context *context)
{
	if (input[context->index] != '\\' || context->state.in_single)
		return (0);
	if (!input[context->index + 1])
	{
		context->index++;
		return (1);
	}
	if (handle_backslash_in_double(input, context))
		return (1);
	context->size++;
	context->index += 2;
	return (1);
}

static void	add_variable_size(char *input, t_data *data, t_size_context *context)
{
	char	*var_name;
	char	*var_value;
	int		tmp_i;

	context->index++;
	if (input[context->index] == '\'' || input[context->index] == '"')
		return ;
	tmp_i = context->index;
	var_name = get_var_name(input, &tmp_i);
	if (!var_name || var_name[0] == '\0')
	{
		context->size += 1;
		free(var_name);
		context->index = tmp_i;
		return ;
	}
	var_value = get_var_value(var_name, data);
	if (var_value)
		context->size += ft_strlen(var_value);
	free(var_value);
	free(var_name);
	context->index = tmp_i;
}

static void	process_char_for_size(char *input, t_data *data, t_size_context *context)
{
	if (handle_backslash_size(input, context))
		return ;
	if (input[context->index] == '\'' && !context->state.in_double)
	{
		context->state.in_single = !context->state.in_single;
		context->size++;
		context->index++;
	}
	else if (input[context->index] == '"' && !context->state.in_single)
	{
		context->state.in_double = !context->state.in_double;
		context->size++;
		context->index++;
	}
	else if (input[context->index] == '$' && !context->state.in_single
		&& should_expand_int_quotes(input, context->index, context->state.in_single))
		add_variable_size(input, data, context);
	else
	{
		context->size++;
		context->index++;
	}
}

int	calculate_expanded_size(char *input, t_data *data)
{
	t_size_context	context;

	if (!input || !data)
		return (-1);
	context.state.in_single = 0;
	context.state.in_double = 0;
	context.index = 0;
	context.size = 0;
	while (input[context.index])
		process_char_for_size(input, data, &context);
	return (context.size);
}
