/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:09:18 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 13:50:36 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*This is the main entry point for variable expansion. It first calculates
the size needed for the expanded string (using calculate_expanded_size).
If successful, it then performs the actual expansion (using perform_expansion)
and returns the expanded string. If any step fails, it returns NULL*/

char	*expand_variables(char *input, t_data *data)
{
	char	*var_name;
	char	*var_value;

	if (!input || !data)
		return (NULL);
	if (input[0] == '$' && input[1] != '\0')
	{
		var_name = input + 1;
		if (ft_strcmp(var_name, "?") == 0)
		{
			return (ft_itoa(data->exit_status));
		}
		var_value = get_env_var(data->envp, var_name);
		if (var_value)
			return (ft_strdup(var_value));
		else
			return (ft_strdup(""));
	}
	return (ft_strdup(input));
}
