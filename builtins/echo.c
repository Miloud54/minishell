/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:51:50 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/18 14:58:09 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The echo command prints on the standard output (stdout) what we've given it as
an argument.

Example: 
$> echo hello world
$> hello world
$> echo hello world | cat -e
$> hello world$

The echo command only has one flag to manage in minishell: -n.
If the flag -n is present, we don't print the final \n.

Example:
$> echo -n hello world
$> hello world%
$> echo -n hello world | cat -e
$> hello world%
*/