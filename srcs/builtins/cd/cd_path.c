/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:52:09 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 13:52:11 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cd_path(char **argv, t_data *data)
{
	char	*home;
	char	*oldpwd;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		home = get_env_var(data->envp, "HOME");
		if (!home)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (home);
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		oldpwd = get_env_var(data->envp, "OLDPWD");
		if (!oldpwd)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (oldpwd);
	}
	return (argv[1]);
}
