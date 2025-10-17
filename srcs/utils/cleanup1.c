/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedidier <emiliedidier@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:50:55 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/17 16:51:33 by emiliedidie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	clear_history_safe(void)
{
	rl_clear_history();
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	clear_history_safe();
	if (data->envp)
	{
		free_envp(data->envp);
		data->envp = NULL;
	}
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
}
