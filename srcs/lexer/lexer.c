/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:35:49 by phautena          #+#    #+#             */
/*   Updated: 2024/10/02 18:54:29 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	lexer(char *input)
// {

// }

int	tokenize_all(char *input)
{
	t_token	*head_token;
	int		i;

	head_token = NULL;
	i = is_hd_sep(input, &head_token);
	return (SUCCESS);
}
int	add_token_end(char *to_tokenize, t_token **head)
{
	t_token	*new_token;
	t_token	*temp;

	if (*head == NULL)
	{
		*head = create_token(to_tokenize);
		if (!head)
			return (ERROR);
		return (SUCCESS);
	}
	new_token = create_token(to_tokenize);
	if (!new_token)
		return (ERROR);
	temp = *head;
	while (temp)
		temp = temp->next;
	new_token->prev = temp;
	new_token->next = NULL;
	temp->next = new_token;
	new_token->value = to_tokenize;
	// new_token->token = tokenize(to_tokenize);
	return (SUCCESS);
}

t_token	*create_token(char *to_tokenize)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->value = to_tokenize;
	// new_token->token = tokenize(to_tokenize);
	return (new_token);
}

int	is_hd_sep(char *input, t_token **head)
{
	char	*to_tokenize;

	if (input[0] == '<' && input[1] == '<')
	{
		to_tokenize = "<<";
		add_token_end(to_tokenize, head);
		return (2);
	}
	return (0);
}

int	get_next_sep(char *input, int i)
{
	while (!is_separator(input[i]))
		i++;
	return (SUCCESS);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '|')
		return (1);
	else if (c == '<' || c == '>')
		return (1);
	else if (c == '\0')
		return (1);
	else
		return (0);
}
