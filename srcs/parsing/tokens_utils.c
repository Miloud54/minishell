/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:01:14 by edidier           #+#    #+#             */
/*   Updated: 2025/10/01 17:21:14 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_token_words(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**tokens_to_argv(t_token *tokens)
{
	char	**argv;
	t_token	*tmp;
	int		i;
	int		count;

	count = count_token_words(tokens);
	argv = ft_calloc(count + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}
