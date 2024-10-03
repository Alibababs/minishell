/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:24:36 by phautena          #+#    #+#             */
/*   Updated: 2024/10/03 11:02:47 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_end(char *to_tokenize, t_token **head)
{
	t_token	*new_token;
	t_token	*temp;

	if (!*head)
		add_token_empty(to_tokenize, head);
	else
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return ;
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		new_token->next = NULL;
		new_token->prev = temp;
		new_token->value = to_tokenize;
		// new_token->token = tokenize();
	}
}

void	add_token_empty(char *to_tokenize, t_token **head)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->value = to_tokenize;
	// new_token->token = tokenize();
	*head = new_token;
}

void	print_token(t_token **head)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *head;
	while (temp)
	{
		printf("TOKEN [%d]\n", i);
		printf("Value: %s\n", temp->value);
		// printf("Token: %s\n", temp->token);
		printf("\n\n");
		temp = temp->next;
		i++;
	}
}
