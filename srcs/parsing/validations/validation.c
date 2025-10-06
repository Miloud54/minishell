/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:31:03 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/02 16:05:16 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Checks that the command line entered by the user has a correct syntax before
parsing it or executing it*/
int		validate_syntax(char *input)
{
	if (!input || !*input)
		return (1);
	if (ft_strnstr(input, "&&", ft_strlen(input)))
	{
		write(2, "minishell: syntax error near unexpected token `&&'\n", 52);
		return (0);
	}
	if (ft_strnstr(input, "||", ft_strlen(input)))
	{
		write(2, "minishell: syntax error near unexpected token `||'\n", 52);
		return (0);
	}
	if (has_unclosed_quotes(input))
	{
		write(2, "minishell: syntax error: unclosed quotes\n", 41);
		return (0);
	}
	if (!validate_pipe_syntax(input))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (0);
	}
	char	*unexpected = validate_redirect_syntax(input);
	if (unexpected)
	{
		write(2, "minishell: syntax error near unexpected token `", 46);
		write(2, unexpected, ft_strlen(unexpected));
		write(2, "'\n", 2);
		free(unexpected);
		return (0);
	}
	return (1);
}
