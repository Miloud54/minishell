/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:52:26 by edidier           #+#    #+#             */
/*   Updated: 2025/10/10 14:47:40 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cd_ctx
{
	char	*path;
	char	**argv;
	char	*cdpath_result;
	char	*expanded;
}			t_cd_ctx;

static int	should_print_path(char **argv, char *cdpath_result)
{
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		return (1);
	if (cdpath_result)
		return (1);
	return (0);
}

static int	perform_cd(t_data *data, t_cd_ctx *ctx)
{
	char	*target;
	int		ret;

	target = ctx->path;
	if (ctx->cdpath_result)
		target = ctx->cdpath_result;
	ret = change_directory(target, ctx->argv[1], data);
	if (ret == 0 && should_print_path(ctx->argv, ctx->cdpath_result))
	{
		ft_putstr_fd(target, 1);
		ft_putchar_fd('\n', 1);
	}
	if (ctx->cdpath_result)
		free(ctx->cdpath_result);
	if (ctx->expanded)
		free(ctx->expanded);
	return (ret);
}

static int	ft_cd_impl(t_data *data, char **argv)
{
	char		*expanded;
	char		*path;
	char		*cdpath_result;
	t_cd_ctx	ctx;

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
	ctx.path = path;
	ctx.argv = argv;
	ctx.cdpath_result = cdpath_result;
	ctx.expanded = expanded;
	return (perform_cd(data, &ctx));
}

int	ft_cd(t_data *data, char **argv)
{
	if (cd_invalid_option(argv, data))
		return (1);
	return (ft_cd_impl(data, argv));
}
