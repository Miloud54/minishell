/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:55:35 by edidier           #+#    #+#             */
/*   Updated: 2025/09/24 18:03:52 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_env_var(const char *name, const char *value)
{
	int		name_len;
	int		value_len;
	char	*new_var;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = malloc(name_len + value_len + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, name);
	new_var[name_len] = '=';
	ft_strcpy(new_var + name_len + 1, value);
	return (new_var);
}

static int	replace_env_var(char **envp, const char *name, char *new_var)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_env_var(char ***envp, char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	i = -1;
	while ((*envp)[++i])
		new_envp[i] = (*envp)[i];
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (0);
}

int	update_env_var(char ***envp, char *name, char *value)
{
	int		i;
	int		name_len;
	char	*new_var;
	char	**new_envp;

	if (!envp || !*envp || !name || !value)
		return (1);
	new_var = create_env_var(name, value);
	if (!new_var)
		return (1);
	if (replace_env_var(*envp, name, new_var))
		return (0);
	if (add_env_var(envp, new_var))
	{
		free(new_var);
		return (1);
	}
	return (0);
}

/*
We use char ***envp (a pointer to a pointer to a pointer) so that we can modify the environment variable array 
itself (not just its contents) inside the function.

Explanation:

If you want to add a new variable,
	you may need to reallocate the array (malloc a bigger array,
	then free the old one).
If you only pass char **envp,
	you are just modifying a local copy of the pointer: the reallocated array will not be visible outside the function.
By passing char ***envp, you can do:
*envp = new_envp;
and the shell’s environment variable pointer will correctly point to the new array.
*/
