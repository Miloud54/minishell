/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:01:14 by edidier           #+#    #+#             */
/*   Updated: 2025/09/24 16:03:20 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokens_to_argv(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	char	**argv;
	int		i;

	count = 0;
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}
