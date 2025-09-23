/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:40 by edidier           #+#    #+#             */
/*   Updated: 2025/09/23 11:49:39 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*Manage the sate (opening/closing) of single quotes in the input 
string to know if we are inside or outside signle quotes */

static int	handle_quote_char(char c, int *in_single_quotes)
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

/*Retrieves the name of an environment variable after a $,
gets its value, and copies this value into the result string*/

static void	expand_and_copy_variable(t_copy_context *ctx)
{
	char	*var_name;
	char	*var_value;

	(*(ctx->i))++;
	var_name = get_var_name(ctx->input, ctx->i);
	var_value = get_var_value(var_name, ctx->data);
	copy_variable_value(var_value, ctx->result, ctx->j);
	free(var_name);
	free(var_value);
}

/*Initializes the context structure used for expansion,setting up 
pointers needed to iterate through the input and write the result*/

static void	init_expansion_context(t_copy_context *ctx, char *input,
		t_data *data, char *result)
{
	static int	i;
	static int	j;

	i = 0;
	j = 0;
	ctx->input = input;
	ctx->data = data;
	ctx->result = result;
	ctx->i = &i;
	ctx->j = &j;
}

/*Iterates through the input string character by character, handles quotes, triggers 
variable expansion if needed, and copies characters or values into the result */

static void	process_expansion_loop(char *input, t_copy_context *ctx,
		int *in_single_quotes)
{
	int	i;

	i = *(ctx->i);
	while (input[i])
	{
		if (handle_quote_char(input[i], in_single_quotes))
			ctx->result[(*(ctx->j))++] = input[i++];
		else if (input[i] == '$' && should_expand_int_quotes(input, i,
				*in_single_quotes))
			expand_and_copy_variable(ctx);
		else
			ctx->result[(*(ctx->j))++] = input[i++];
		*(ctx->i) = i;
		i = *(ctx->i);
	}
}

/*Main function called to perform expansion: allocates the result buffer, initializes the 
context, runs the expansion loop, terminates the string, and returns the result*/

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

/*Each function helps manage environment variable expansion 
in a shell command, following the rules for quotes.*/
