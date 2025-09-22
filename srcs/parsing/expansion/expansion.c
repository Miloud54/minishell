/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:09:18 by edidier           #+#    #+#             */
/*   Updated: 2025/09/22 16:51:30 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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
