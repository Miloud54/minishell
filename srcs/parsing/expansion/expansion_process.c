/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:40 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 15:04:46 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes_expansion(char c, t_quote_params *params)
{
	if (c == '\'' && !(*(params->in_single_quotes)))
	{
		*(params->in_single_quotes) = 1;
		params->result[(*(params->j))++] = c;
		(*(params->i))++;
		return (1);
	}
	else if (c == '\'' && *(params->in_single_quotes))
	{
		*(params->in_single_quotes) = 0;
		params->result[(*(params->j))++] = c;
		(*(params->i))++;
		return (1);
	}
	return (0);
}

void	process_variable_expansion(t_expand_params *params)
{
	char	*var_name;
	char	*var_value;

	(*(params->i))++;
	var_name = get_var_name(params->input, params->i);
	var_value = get_var_value(var_name, params->data);
	copy_variable_value(var_value, params->result, params->j);
	free(var_name);
	free(var_value);
}

static t_expansion_vars	*init_expansion_vars(void)
{
	static t_expansion_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.in_single_quotes = 0;
	return (&vars);
}

static void	expansion_loop(char *input, t_quote_params *q_params,
		t_expand_params *e_params)
{
	int	i;
	int	j;

	i = *(q_params->i);
	j = *(q_params->j);
	while (input[i])
	{
		if (handle_quotes_expansion(input[i], q_params))
		{
			i = *(q_params->i);
			j = *(q_params->j);
			continue ;
		}
		else if (input[i] == '$' && should_expand_int_quotes(input, i,
				*(q_params->in_single_quotes)))
			process_variable_expansion(e_params);
		else
		{
			q_params->result[j++] = input[i++];
			*(q_params->i) = i;
			*(q_params->j) = j;
		}
		i = *(q_params->i);
		j = *(q_params->j);
	}
}

char	*perform_expansion(char *input, t_data *data, int expanded_size)
{
	char				*result;
	t_quote_params		q_params;
	t_expand_params		e_params;
	t_expansion_vars	*vars;

	result = malloc(expanded_size + 1);
	if (!result)
		return (NULL);
	vars = init_expansion_vars();
	q_params.result = result;
	q_params.in_single_quotes = &vars->in_single_quotes;
	q_params.j = &vars->j;
	q_params.i = &vars->i;
	e_params.input = input;
	e_params.data = data;
	e_params.i = &vars->i;
	e_params.result = result;
	e_params.j = &vars->j;
	expansion_loop(input, &q_params, &e_params);
	result[vars->j] = '\0';
	return (result);
}
