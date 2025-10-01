/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:35 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 16:55:53 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*Manages the state of single quotes in the input string, to know
if you are inside or outside single quotes (for expansion rules)*/

static int	handle_quote_char_size(char c, int *in_single_quotes)
{
	if (c == '\'' && !(*in_single_quotes))
	{
		*in_single_quotes = 1;
		return (1);
	}
	else if (c == '\'' && *in_single_quotes)
	{
		*in_single_quotes = 0;
		return (1);
	}
	return (0);
}

/*When a variable is detected, gets its name and value, and adds the
length of the value to the total size needed for the expanded string*/

static void	add_variable_size(char *input, t_data *data, int *i, int *size)
{
	char	*var_name;
	char	*var_value;
	int		temp_i;

	(*i)++;
	temp_i = *i;
	var_name = get_var_name(input, &temp_i);
	var_value = get_var_value(var_name, data);
	*size += ft_strlen(var_value);
	free(var_name);
	free(var_value);
	*i = temp_i;
}

/*Processes the current character in the input; handles quotes, triggers
variable size calculation if needed, or just increments the size for normal
characters*/

static void	process_char_for_size(t_size_context *ctx)
{
	if (handle_quote_char_size(ctx->input[*(ctx->i)], ctx->in_single_quotes))
	{
		(*(ctx->size))++;
		(*(ctx->i))++;
	}
	else if (ctx->input[*(ctx->i)] == '$'
		&& should_expand_int_quotes(ctx->input, *(ctx->i),
			*(ctx->in_single_quotes)))
		add_variable_size(ctx->input, ctx->data, ctx->i, ctx->size);
	else
	{
		(*(ctx->size))++;
		(*(ctx->i))++;
	}
}

/*Main function that iterates through the input string, using the above 
helpers, to compute and return the total size required for the string
after all expansions*/

int	calculate_expanded_size(char *input, t_data *data)
{
	int				i;
	int				size;
	int				in_single_quotes;
	t_size_context	ctx;

	if (!input || !data)
		return (-1);
	i = 0;
	size = 0;
	in_single_quotes = 0;
	ctx.input = input;
	ctx.data = data;
	ctx.i = &i;
	ctx.size = &size;
	ctx.in_single_quotes = &in_single_quotes;
	while (input[i])
		process_char_for_size(&ctx);
	return (size);
}

/*These functions work together to determine how much memory is needed to store
 the input string after all environment variable expansions are performed,
 respecting quote rules*/