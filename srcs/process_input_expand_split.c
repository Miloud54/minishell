/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_expand_split.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:20:12 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 16:40:36 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_split_escape(char *arg, int *index, t_quote_state *state)
{
	if (arg[*index] != '\\' || state->in_single)
		return (0);
	if (state->in_double && arg[*index + 1] == '\n')
	{
		*index += 2;
		return (1);
	}
	if (state->in_double && ft_strchr("\"$\\`", arg[*index + 1]))
	{
		*index += 2;
		return (1);
	}
	if (!state->in_double && arg[*index + 1])
	{
		*index += 2;
		return (1);
	}
	return (0);
}

static int	find_field_end(char *arg, int index)
{
	t_quote_state	state;

	state.in_single = 0;
	state.in_double = 0;
	while (arg[index])
	{
		if (handle_split_escape(arg, &index, &state))
			continue ;
		if (arg[index] == '\'' && !state.in_double)
			state.in_single = !state.in_single;
		else if (arg[index] == '"' && !state.in_single)
			state.in_double = !state.in_double;
		else if (!state.in_single && !state.in_double && IS_IFS(arg[index]))
			break ;
		index++;
	}
	return (index);
}

static int	store_new_field(char *arg, int *index, t_dyn_array *fields)
{
	int		end;
	char	*field;

	end = find_field_end(arg, *index);
	field = ft_substr(arg, *index, end - *index);
	if (!field)
		return (0);
	if (!append_field(fields, field))
	{
		free(field);
		return (0);
	}
	*index = end;
	return (1);
}

static int	add_next_field(char *arg, int *index, t_dyn_array *fields)
{
	int	status;

	while (arg[*index] && IS_IFS(arg[*index]))
		(*index)++;
	if (!arg[*index])
		return (0);
	status = store_new_field(arg, index, fields);
	if (!status)
		return (-1);
	return (1);
}

char	**split_expanded_argument(char *arg)
{
	t_dyn_array	fields;
	int			i;
	int			status;

	fields.items = NULL;
	fields.count = 0;
	fields.capacity = 0;
	i = 0;
	status = 1;
	while (arg && arg[i] && status > 0)
		status = add_next_field(arg, &i, &fields);
	if (status < 0)
	{
		ft_free_split(&fields.items);
		return (NULL);
	}
	if (!fields.items)
		fields.items = ft_calloc(1, sizeof(char *));
	if (!fields.items)
		return (NULL);
	return (fields.items);
}
