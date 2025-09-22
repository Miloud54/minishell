/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:30 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 14:56:39 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *input, int *i)
{
	int	start;
	int	end;

	start = *i;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	end = *i;
	if (end == start)
		return (ft_strdup(""));
	return (ft_substr(input, start, end - start));
}

char	*get_var_value(char *var_name, t_data *data)
{
	char	*value;
	char	*exit_code_str;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		exit_code_str = ft_itoa(data->exit_status);
		if (!exit_code_str)
			return (ft_strdup(""));
		return (exit_code_str);
	}
	value = get_env_var(data->envp, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	should_expand_int_quotes(char *input, int i, int in_single_quotes)
{
	(void)input;
	(void)i;
	return (!in_single_quotes);
}

void	copy_variable_value(char *var_value, char *result, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
		result[(*j)++] = var_value[k++];
}
