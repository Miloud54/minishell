/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:35 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 14:56:39 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char c, int *in_single_quotes, int *size, int *i)
{
	if (c == '\'' && !(*in_single_quotes))
	{
		*in_single_quotes = 1;
		(*size)++;
		(*i)++;
		return (1);
	}
	else if (c == '\'' && *in_single_quotes)
	{
		*in_single_quotes = 0;
		(*size)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	handle_variable_expansion(char *input, t_data *data, int *i, int *size)
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

int	calculate_expanded_size(char *input, t_data *data)
{
	int	i;
	int	size;
	int	in_single_quotes;

	i = 0;
	size = 0;
	in_single_quotes = 0;
	while (input[i])
	{
		if (handle_quotes(input[i], &in_single_quotes, &size, &i))
			continue ;
		else if (input[i] == '$' && should_expand_int_quotes(input, i,
				in_single_quotes))
			handle_variable_expansion(input, data, &i, &size);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
