/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:22:43 by edidier           #+#    #+#             */
/*   Updated: 2025/07/26 20:14:29 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static void	set_null_cmd(t_pipex *pipex, int array_idx)
{
	pipex->cmd_paths[array_idx] = NULL;
	pipex->cmd_args[array_idx] = NULL;
}

static void	process_single_cmd(t_pipex *pipex, char *cmd_str, int array_idx,
		char **envp)
{
	char	**cmd_args;

	if (!cmd_str || !*cmd_str)
	{
		set_null_cmd(pipex, array_idx);
		return ;
	}
	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args || !cmd_args[0] || !cmd_args[0][0])
	{
		if (cmd_args)
			ft_free_split(&cmd_args);
		set_null_cmd(pipex, array_idx);
		return ;
	}
	pipex->cmd_paths[array_idx] = get_cmd_path(cmd_args[0], envp);
	if (!pipex->cmd_paths[array_idx])
	{
		ft_free_split(&cmd_args);
		set_null_cmd(pipex, array_idx);
		return ;
	}
	pipex->cmd_args[array_idx] = cmd_args;
}

void	ft_parse_cmds(t_pipex *pipex, char **av, int ac, char **envp)
{
	int	i;
	int	cmd_count;
	int	start_index;

	cmd_count = get_cmd_count(pipex, ac);
	start_index = get_cmd_start_index(pipex);
	if (cmd_count <= 0)
		exit((ft_printf("No commands to process\n"), 127));
	pipex->cmd_paths = ft_calloc(cmd_count, sizeof(char *));
	pipex->cmd_args = ft_calloc(cmd_count, sizeof(char **));
	if (!pipex->cmd_paths || !pipex->cmd_args)
		exit(127);
	pipex->cmd_count = cmd_count;
	i = start_index;
	while (i < ac - 1)
	{
		process_single_cmd(pipex, av[i], get_array_index(pipex, i), envp);
		i++;
	}
}
