/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:35 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:29:16 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	handle_backslash_in_double(char *input, t_size_ctx *ctx)
{
	if (!ctx->state.in_double)
		return (0);
	if (input[ctx->index + 1] == '\n')
	{
		ctx->index += 2;
		return (1);
	}
	if (ft_strchr("\"$\\`", input[ctx->index + 1]))
	{
		ctx->size++;
		ctx->index += 2;
		return (1);
	}
	ctx->size++;
	ctx->index++;
	return (1);
}

static int	handle_backslash_size(char *input, t_size_ctx *ctx)
{
	if (input[ctx->index] != '\\' || ctx->state.in_single)
		return (0);
	if (!input[ctx->index + 1])
	{
		ctx->index++;
		return (1);
	}
	if (handle_backslash_in_double(input, ctx))
		return (1);
	ctx->size++;
	ctx->index += 2;
	return (1);
}

static void	add_variable_size(char *input, t_data *data, t_size_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	int		temp_i;

	ctx->index++;
	if (input[ctx->index] == '\'' || input[ctx->index] == '"')
		return ;
	temp_i = ctx->index;
	var_name = get_var_name(input, &temp_i);
	if (!var_name || var_name[0] == '\0')
	{
		ctx->size += 1;
		free(var_name);
		ctx->index = temp_i;
		return ;
	}
	var_value = get_var_value(var_name, data);
	if (var_value)
		ctx->size += ft_strlen(var_value);
	free(var_value);
	free(var_name);
	ctx->index = temp_i;
}

static void	process_char_for_size(char *input, t_data *data, t_size_ctx *ctx)
{
	if (handle_backslash_size(input, ctx))
		return ;
	if (input[ctx->index] == '\'' && !ctx->state.in_double)
	{
		ctx->state.in_single = !ctx->state.in_single;
		ctx->size++;
		ctx->index++;
	}
	else if (input[ctx->index] == '"' && !ctx->state.in_single)
	{
		ctx->state.in_double = !ctx->state.in_double;
		ctx->size++;
		ctx->index++;
	}
	else if (input[ctx->index] == '$' && !ctx->state.in_single
		&& should_expand_int_quotes(input, ctx->index, ctx->state.in_single))
		add_variable_size(input, data, ctx);
	else
	{
		ctx->size++;
		ctx->index++;
	}
}

int	calculate_expanded_size(char *input, t_data *data)
{
	t_size_ctx	ctx;

	if (!input || !data)
		return (-1);
	ctx.state.in_single = 0;
	ctx.state.in_double = 0;
	ctx.index = 0;
	ctx.size = 0;
	while (input[ctx.index])
		process_char_for_size(input, data, &ctx);
	return (ctx.size);
}
