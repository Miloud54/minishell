/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:40 by edidier           #+#    #+#             */
/*   Updated: 2025/10/13 17:07:50 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	expand_and_copy_variable(t_copy_context *ctx)
{
	char	*var_name;
	char	*var_value;
	char	next_char;

	(*(ctx->i))++;
	next_char = ctx->input[*(ctx->i)];
	if (!next_char || next_char == '\'' || next_char == '"')
	{
		ctx->result[(*(ctx->j))++] = '$';
		return ;
	}
	var_name = get_var_name(ctx->input, ctx->i);
	if (!var_name || var_name[0] == '\0')
	{
		ctx->result[(*(ctx->j))++] = '$';
		free(var_name);
		return ;
	}
	var_value = get_var_value(var_name, ctx->data);
	copy_variable_value(var_value, ctx->result, ctx->j);
	free(var_value);
	free(var_name);
}

static int	handle_backslash_copy(char *input, t_copy_context *ctx,
		t_quote_state *state, int i)
{
	if (input[i] != '\\' || state->in_single)
		return (i);
	if (!input[i + 1])
		return (i + 1);
	if (state->in_double && input[i + 1] == '\n')
		return (i + 2);
	if (state->in_double && ft_strchr("\"$\\`", input[i + 1]))
	{
		ctx->result[(*(ctx->j))++] = input[i + 1];
		return (i + 2);
	}
	if (!state->in_double)
	{
		ctx->result[(*(ctx->j))++] = input[i + 1];
		return (i + 2);
	}
	ctx->result[(*(ctx->j))++] = input[i];
	return (i + 1);
}

static int	handle_expansion_char(char *input, t_copy_context *ctx,
		t_quote_state *state, int i)
{
	int	next;

	next = handle_backslash_copy(input, ctx, state, i);
	if (next != i)
		return (next);
	if (input[i] == '\'' && !state->in_double)
	{
		ctx->result[(*(ctx->j))++] = input[i++];
		state->in_single = !state->in_single;
	}
	else if (input[i] == '"' && !state->in_single)
	{
		ctx->result[(*(ctx->j))++] = input[i++];
		state->in_double = !state->in_double;
	}
	else if (input[i] == '$' && !state->in_single
		&& should_expand_int_quotes(input, i, state->in_single))
	{
		*(ctx->i) = i;
		expand_and_copy_variable(ctx);
		i = *(ctx->i);
	}
	else
		ctx->result[(*(ctx->j))++] = input[i++];
	return (i);
}

static void	process_expansion_loop(char *input, t_copy_context *ctx,
		int *in_single_quotes)
{
	int				i;
	t_quote_state	state;

	i = *(ctx->i);
	state.in_single = 0;
	state.in_double = 0;
	while (input[i])
	{
		i = handle_expansion_char(input, ctx, &state, i);
		*(ctx->i) = i;
	}
	*in_single_quotes = state.in_single;
}

char	*perform_expansion(char *input, t_data *data, int expanded_size)
{
	char			*result;
	int				in_single_quotes;
	t_copy_context	ctx;

	if (!input || !data || expanded_size < 0)
		return (NULL);
	result = malloc(expanded_size + 1);
	if (!result)
		return (NULL);
	in_single_quotes = 0;
	init_expansion_context(&ctx, input, data, result);
	process_expansion_loop(input, &ctx, &in_single_quotes);
	result[*(ctx.j)] = '\0';
	return (result);
}
