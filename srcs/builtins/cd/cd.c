/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/15 18:16:04 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_print_path(char **argv, char *cdpath_result)
{
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		return (1);
	if (cdpath_result)
		return (1);
	return (0);
}

static void	print_target_if_needed(t_data *data, t_cd_context *context,
		int ret, int print_path)
{
	char	*to_print;

	if (ret != 0 || !print_path)
		return ;
	to_print = context->cdpath_result;
	if (!to_print)
		to_print = get_env_var(data->envp, "PWD");
	if (to_print)
	{
		ft_putstr_fd(to_print, 1);
		ft_putchar_fd('\n', 1);
	}
}

static int	perform_cd(t_data *data, t_cd_context *context)
{
	char	*target;
	int		ret;
	int		print_path;

	target = context->path;
	if (context->cdpath_result)
		target = context->cdpath_result;
	print_path = should_print_path(context->argv, context->cdpath_result);
	ret = change_directory(target, context->argv[1], data);
	print_target_if_needed(data, context, ret, print_path);
	if (context->cdpath_result)
		free(context->cdpath_result);
	if (context->expanded)
		free(context->expanded);
	return (ret);
}

static int	ft_cd_impl(t_data *data, char **argv)
{
	char			*expanded;
	char			*path;
	char			*cdpath_result;
	t_cd_context	context;

	expanded = NULL;
	cdpath_result = NULL;
	path = cd_resolve_path(argv, data, &expanded);
	if (!path)
	{
		data->exit_status = 1;
		if (expanded)
			free(expanded);
		return (1);
	}
	if (cd_handle_home_empty(argv, path, data, expanded))
		return (0);
	if (cd_handle_too_many_arguments(argv, data, expanded))
		return (1);
	cdpath_result = cd_apply_cdpath_if_needed(argv, path, data, expanded);
	context.path = path;
	context.argv = argv;
	context.cdpath_result = cdpath_result;
	context.expanded = expanded;
	return (perform_cd(data, &context));
}

int	ft_cd(t_data *data, char **argv)
{
	if (cd_invalid_option(argv, data))
		return (1);
	return (ft_cd_impl(data, argv));
}
