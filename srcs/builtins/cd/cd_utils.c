/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:51:53 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 14:21:00 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_directory(const char *path, t_data *data)
{
	struct stat	st;

	if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

void	print_cd_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	cd_count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	cd_handle_too_many_arguments(char **argv, t_data *data, char *expanded)
{
	int	argc;

	argc = cd_count_args(argv);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->exit_status = 1;
		if (expanded)
			free(expanded);
		return (1);
	}
	return (0);
}

int	cd_invalid_option(char **argv, t_data *data)
{
	if (argv[1] && argv[1][0] == '-' && argv[1][1]
		&& !(argv[1][1] == '\0' || (argv[1][1] == '-' && argv[1][2] == '\0')))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("cd: usage: cd [dir]\n", 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}
