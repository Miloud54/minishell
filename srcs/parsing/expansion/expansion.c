/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:09:18 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 15:11:26 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
