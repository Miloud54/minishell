/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:09:18 by edidier           #+#    #+#             */
/*   Updated: 2025/09/23 11:54:55 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*Main entry point for variable expansion. It first calculates the size needed for 
the expanded string (using calculate_expanded_size). If successful, it then performs 
the actual expansion (using perform_expansion) and returns the expanded string. If any 
step fails, it returns NULL*/

char	*expand_variables(char *input, t_data *data)
{
	int	expanded_size;

	if (!input || !data)
		return (NULL);
	expanded_size = calculate_expanded_size(input, data);
	if (expanded_size < 0)
		return (NULL);
	return (perform_expansion(input, data, expanded_size));
}
