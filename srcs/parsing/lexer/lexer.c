/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:28:52 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/22 15:23:38 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Checks if the character is a special shell operator (<, >, |) */
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* Skips over quoted sections in the input string */
int	skip_quotes(char *input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

/* Extracts a word from the input, handling quotes and special chars */
char	*extract_word(char *input, int *i)
{
	int		start;
	int		end;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			*i = skip_quotes(input, *i, input[*i]);
		else
			(*i)++;
	}
	end = *i;
	word = ft_substr(input, start, end - start);
	return (word);
}

/* Tokenizes the input string into a linked list of tokens */
t_token	*lexer(char *input)
{
	int		i;
	t_token	*tokens;
	t_token	*new_token;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
			new_token = handle_pipe_token(&i);
		else if (is_special_char(input[i]))
			new_token = handle_redirect_token(input, &i);
		else
			new_token = handle_word_token(input, &i);
		add_token(&tokens, new_token);
	}
	return (tokens);
}
