/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:43:58 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 14:44:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_resolve_path(char **argv, t_data *data, char **expanded)
{
	*expanded = NULL;
	if (argv[1] && argv[1][0] == '$')
	{
		*expanded = expand_env_var(argv[1], data->envp);
		if (!*expanded)
		{
			if (ft_strcmp(argv[1], "$HOME") == 0)
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
				data->exit_status = 1;
			}
			return (NULL);
		}
	}
	if (*expanded)
		return (*expanded);
	return (get_cd_path(argv, data));
}

char	*cd_apply_cdpath_if_needed(char **argv, char *path, t_data *data,
		char *expanded)
{
	char	*cdpath_result;

	cdpath_result = NULL;
	if (!argv[1] || expanded)
		return (NULL);
	if (argv[1][0] == '/' || argv[1][0] == '.')
		return (NULL);
	if (path && (path[0] == '/' || path[0] == '.'))
		return (NULL);
	cdpath_result = try_cdpath(argv[1], data->envp);
	return (cdpath_result);
}

int	cd_handle_home_empty(char **argv, char *path, t_data *data, char *expanded)
{
	if ((argv[1] == NULL || (argv[1] && ft_strcmp(argv[1], "~") == 0))
		&& path && path[0] == '\0')
	{
		data->exit_status = 0;
		if (expanded)
			free(expanded);
		return (1);
	}
	return (0);
}
