/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:51:51 by edidier           #+#    #+#             */
/*   Updated: 2025/10/21 20:27:03 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	update_quote_state(char c, t_quote_state *state)
{
	if (c == '\'' && !state->in_double)
		state->in_single = !state->in_single;
	else if (c == '"' && !state->in_single)
		state->in_double = !state->in_double;
}

int	has_unquoted_sequence(char *input, const char *sequence)
{
	t_quote_state	state;
	size_t			len;
	int				i;

	if (!input || !sequence)
		return (0);
	state = (t_quote_state){0, 0};
	len = ft_strlen(sequence);
	i = 0;
	while (input[i])
	{
		update_quote_state(input[i], &state);
		if (!state.in_single && !state.in_double
			&& ft_strncmp(input + i, sequence, len) == 0)
			return (1);
		i++;
	}
	return (0);
}
