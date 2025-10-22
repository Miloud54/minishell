/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:54:30 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:50:33 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*Extracts the variable name from the input string starting at position *i.
Handles special case for $? (exit code). Advances *i past the variable name*/

char	*get_var_name(char *input, int *i)
{
	int	start;
	int	end;

	if (!input || !i || *i < 0)
		return (ft_strdup(""));
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

/*Returns the value of the given variable name from the environment (data).
If the variable is "?", returns the shell's last exit status
as a string. Returns an empty string if not found*/

char	*get_var_value(char *var_name, t_data *data)
{
	char	*value;
	char	*exit_code_str;

	if (!var_name || !data)
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

/*Returns whether variable expansion should occur, depending on if
we are inside single quotes (returns false if inside single quotes)*/

int	should_expand_int_quotes(char *input, int i, int in_single_quotes)
{
	(void)input;
	(void)i;
	return (!in_single_quotes);
}

/*Copies the value of a variable (var_value) into the
result string at position *j, character by character*/

void	copy_variable_value(char *var_value, char *result, int *j)
{
	int	k;

	if (!var_value || !result || !j)
		return ;
	k = 0;
	while (var_value[k])
		result[(*j)++] = var_value[k++];
}

/*These functions are used to extract, resolve, and copy 
environment variable values during the expansion process.*/
