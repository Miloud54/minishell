/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_expand_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:32:11 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 16:10:39 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	grow_array(t_dyn_array *array)
{
	char	**tmp;
	int		i;
	int		new_cap;

	if (array->capacity == 0)
		new_cap = 4;
	else
		new_cap = array->capacity * 2;
	tmp = ft_calloc(new_cap, sizeof(char *));
	if (!tmp)
		return (0);
	i = 0;
	while (i < array->count)
	{
		tmp[i] = array->items[i];
		i++;
	}
	free(array->items);
	array->items = tmp;
	array->capacity = new_cap;
	return (1);
}

static void	clear_fields(char **fields, int start)
{
	int	i;

	i = start;
	while (fields && fields[i])
	{
		free(fields[i]);
		i++;
	}
	free(fields);
}

static int	append_clean_field(char **fields, t_dyn_array *args, int index)
{
	char	*clean;

	clean = remove_quotes(fields[index]);
	if (!clean)
	{
		clear_fields(fields, index);
		return (0);
	}
	free(fields[index]);
	fields[index] = NULL;
	if (!append_field(args, clean))
	{
		free(clean);
		clear_fields(fields, index + 1);
		return (0);
	}
	return (1);
}

int	append_field(t_dyn_array *fields, char *value)
{
	if (fields->capacity <= fields->count)
	{
		if (!grow_array(fields))
			return (0);
	}
	fields->items[fields->count] = value;
	fields->count++;
	fields->items[fields->count] = NULL;
	return (1);
}

int	append_clean_fields(char **fields, t_dyn_array *args)
{
	int		i;

	if (!fields)
		return (1);
	i = 0;
	while (fields[i])
	{
		if (!append_clean_field(fields, args, i))
			return (0);
		i++;
	}
	free(fields);
	return (1);
}
