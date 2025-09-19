/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_v1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-la-p <bde-la-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:18:30 by bde-la-p          #+#    #+#             */
/*   Updated: 2025/09/19 18:57:09 by bde-la-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next_token;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next_token = current->next;
		free(current->value);
		free(current);
		current = next_token;
	}
	*head = NULL;
}

static t_token	*create_token(char *value, int type)
{
	t_token	*new_token;
	
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

int		append_token(t_token **head, char *value, int type)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(value, type);
	if (!new_token)
		return (0);
	if (!*head)
	{
		*head = new_token;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
	return (1);
}

bool	is_operator(char *word)
{
	if (!word)
		return (false);
	return (ft_strcmp(word, "<") == 0 || ft_strcmp(word, "<<") == 0
		|| ft_strcmp(word, ">") == 0 || ft_strcmp(word, ">>") == 0
		|| ft_strcmp(word, "|") == 0);
}

int		get_token_type(char *word)
{
	if (ft_strcmp(word, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(word, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(word, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(word, ">>") == 0)
		return (TOKEN_APPEND);
	if (ft_strcmp(word, "|") == 0)
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

static void	identify_commands(t_token *tokens)
{
	t_token	*current;
	t_token	*first_non_file;

	current = tokens;
	while (current)
	{
		first_non_file = NULL;
		
		// Chercher le premier word qui n'est PAS un fichier
		while (current && current->type != TOKEN_PIPE)
		{
			if (current->type == TOKEN_WORD && !first_non_file)
			{
				bool is_file = false;
				
				// C'est un fichier si c'est après une redirection
				if (current->prev && 
					(current->prev->type == TOKEN_REDIR_IN ||
					 current->prev->type == TOKEN_REDIR_OUT || 
					 current->prev->type == TOKEN_APPEND || 
					 current->prev->type == TOKEN_HEREDOC))
				{
					is_file = true;
				}
				
				if (!is_file)
				{
					first_non_file = current;
				}
			}
			current = current->next;
		}
		
		// Le premier non-fichier devient la commande
		if (first_non_file)
			first_non_file->type = TOKEN_CMD;
		
		// Passer au segment suivant
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
}

t_token		*tokenize(char *line)
{
	char	**words;
	t_token	*tokens;
	int		i;
	int		type;

	tokens = NULL;
	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		type = get_token_type(words[i]);
		if (!append_token(&tokens, words[i], type))
		{
			free_tokens(&tokens);
			free_array(words);
			return (NULL);
		}
		i++;
	}
	free_array(words);
	identify_commands(tokens);
	return (tokens);
}

/*Debugging function: */
void	print_tokens(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	i = 1;
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("Token %d: \"%s\" (type: %d)\n", i, current->value, current->type);
		current = current->next;
		i++;
	}
	printf("==============\n");
}