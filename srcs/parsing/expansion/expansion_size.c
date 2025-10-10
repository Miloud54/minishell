/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:35 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 16:41:03 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	handle_backslash_size(char *input, t_quote_state *state, int *i,
		int *size)
{
	if (input[*i] != '\\' || state->in_single)
		return (0);
	if (!input[*i + 1])
	{
		(*i)++;
		return (1);
	}
	if (state->in_double && input[*i + 1] == '\n')
	{
		*i += 2;
		return (1);
	}
	if (state->in_double && ft_strchr("\"$\\`", input[*i + 1]))
	{
		(*size)++;
		*i += 2;
		return (1);
	}
	if (!state->in_double)
	{
		(*size)++;
		*i += 2;
		return (1);
	}
	(*size)++;
	(*i)++;
	return (1);
}

static void	add_variable_size(char *input, t_data *data, int *i, int *size)
{
	char	*var_name;
	char	*var_value;
	int		temp_i;

	(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
		return ;
	temp_i = *i;
	var_name = get_var_name(input, &temp_i);
	if (!var_name || var_name[0] == '\0')
	{
		*size += 1;
		free(var_name);
		*i = temp_i;
		return ;
	}
	var_value = get_var_value(var_name, data);
	if (var_value)
		*size += ft_strlen(var_value);
	free(var_value);
	free(var_name);
	*i = temp_i;
}

static void	process_char_for_size(char *input, t_data *data, int *i, int *size,
		t_quote_state *state)
{
	if (handle_backslash_size(input, state, i, size))
		return ;
	if (input[*i] == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		(*size)++;
		(*i)++;
	}
	else if (input[*i] == '"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		(*size)++;
		(*i)++;
	}
	else if (input[*i] == '$' && !state->in_single
		&& should_expand_int_quotes(input, *i, state->in_single))
		add_variable_size(input, data, i, size);
	else
	{
		(*size)++;
		(*i)++;
	}
}

int	calculate_expanded_size(char *input, t_data *data)
{
	t_quote_state	state;
	int				i;
	int				size;

	if (!input || !data)
		return (-1);
	state.in_single = 0;
	state.in_double = 0;
	i = 0;
	size = 0;
	while (input[i])
		process_char_for_size(input, data, &i, &size, &state);
	return (size);
}
