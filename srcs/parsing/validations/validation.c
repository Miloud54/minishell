/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:31:03 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/10/10 17:11:32 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	print_token_error(const char *token)
{
	ft_putstr_fd((char *)"minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)token, 2);
	ft_putstr_fd((char *)"'\n", 2);
	return (0);
}

static int	check_basic_syntax(char *input)
{
	if (!input || !*input)
		return (1);
	if (ft_strnstr(input, "&&", ft_strlen(input)))
		return (print_token_error("&&"));
	if (ft_strnstr(input, "||", ft_strlen(input)))
		return (print_token_error("||"));
	if (has_unclosed_quotes(input))
		return (print_token_error("unclosed quotes"));
	return (-1);
}

static int	check_unexpected(char *(*validate_fn)(char *), char *input)
{
	char	*unexpected;

	unexpected = validate_fn(input);
	if (unexpected)
	{
		print_token_error(unexpected);
		free(unexpected);
		return (0);
	}
	return (-1);
}

/* Checks that the command line entered by the user has a correct syntax before
parsing it or executing it*/
int	validate_syntax(char *input)
{
	int	res;

	res = check_basic_syntax(input);
	if (res != -1)
		return (res);
	if (check_unexpected(validate_pipe_syntax, input) == 0)
		return (0);
	if (check_unexpected(validate_redirect_syntax, input) == 0)
		return (0);
	return (1);
}
